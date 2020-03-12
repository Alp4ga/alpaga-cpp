/*
  * @Author: Alpaga
  * @Date: 2020-02-28 10:34:34
  * @Last Modified by:   Alpaga
  * @Last Modified time: 2020-02-28 10:34:34
*/

#include "Ratclikff.hpp"

int rsimil(const char *a, int alen, const char *b, int blen, int cs) {
	int i, j, k, l, p = 0, q = 0, len = 0, left = 0, right = 0;
	/* Find a matching substring */
	for (i = 0; i < alen - len; i++) {
		for (j = 0; j < blen - len; j++) {
			if (cs) {
				if (a[i] == b[j] && a[i + len] == b[j + len]) {
					/* Find out whether this is the longest match */
					for (k = i + 1, l = j + 1; a[k] == b[l] && k < alen && l < blen; k++, l++);
					if (k - i > len) {
						p = i;
						q = j;
						len = k - i;
					}
				}
			} else {
				if (tolower(a[i]) == tolower(b[j]) && tolower(a[i + len]) == tolower(b[j + len])) {
							/* Find out whether this is the longest match */
					for (k = i + 1, l = j + 1; tolower(a[k]) == tolower(b[l]) && k < alen && l < blen; k++, l++);
					if (k - i > len) {
						p = i;
						q = j;
						len = k - i;
					}
				}
			}
		}
	}
	/* No match */
	if (len == 0)
		return 0;

	/* Match the strings to the left */
	if (p != 0 && q != 0)
		left = rsimil(a, p, b, q, cs);

	i = (p + len);
	alen -= i;
	j = (q + len);
	blen -= j;

	/* Match the strings to the right */
	if (alen != 0 && blen != 0)
		right = rsimil(a + i, alen, b + j, blen, cs);

	/* Return the score */
	return len + left + right;
}

double Alpaga::Distance::ratclikffObershelp(const char *a, const char *b) {
	int alen, blen;

	alen = static_cast<int>(strlen(a));
	blen = static_cast<int>(strlen(b));

	if (alen == 0 || blen == 0)
		return 0;

	return (rsimil(a, alen, b, blen, 0) * 200) / (100*(alen + blen));
}