/*
  * @Author: Alpaga
  * @Date: 2020-02-28 10:34:34
  * @Last Modified by:   Alpaga
  * @Last Modified time: 2020-02-28 10:34:34
*/

#include "JaroWinkler.hpp"

#include <algorithm>
#include <vector>
#include <string>

static const double JARO_WEIGHT_STRING_A(1.0/3.0);
static const double JARO_WEIGHT_STRING_B(1.0/3.0);
static const double JARO_WEIGHT_TRANSPOSITIONS(1.0/3.0);

static int JARO_WINKLER_PREFIX_SIZE(4);
static const double JARO_WINKLER_SCALING_FACTOR(0.1);
static const double JARO_WINKLER_BOOST_THRESHOLD(0.7);

double jaroDistance(const std::string &a, const std::string &b) {
	int aLength(static_cast<int>(a.size()));
	int bLength(static_cast<int>(b.size()));
			
	// If one string has null length, we return 0.
	if (aLength == 0 || bLength == 0) {
		return 0.0;
	}
			
	// Calculate max length range.
	int maxRange(std::max(0, std::max(aLength, bLength) / 2 - 1));
			
	// Creates 2 vectors of integers.
	std::vector<bool> aMatch(aLength, false);
	std::vector<bool> bMatch(bLength, false);
			
	// Calculate matching characters.
	int matchingCharacters(0);
	for (int aIndex(0); aIndex < aLength; ++aIndex) {
		// Calculate window test limits (limit inferior to 0 and superior to bLength).
		int minIndex(std::max(aIndex - maxRange, 0));
		int maxIndex(std::min(aIndex + maxRange + 1, bLength));
		
		if (minIndex >= maxIndex) {
			// No more common character because we don't have characters in b to test with characters in a.
			break;
		}
				
		for (int bIndex(minIndex); bIndex < maxIndex; ++bIndex) {
			if (!bMatch.at(bIndex) && a.at(aIndex) == b.at(bIndex)) {
				// Found some new match.
				aMatch[aIndex] = true;
				bMatch[bIndex] = true;
				++matchingCharacters;
					break;
			}
		}
	}
			
	// If no matching characters, we return 0.
	if (matchingCharacters == 0) {
		return 0.0;
	}
			
	// Calculate character transpositions.
	std::vector<int> aPosition(matchingCharacters, 0);
	std::vector<int> bPosition(matchingCharacters, 0);
			
	for (int aIndex(0), positionIndex(0); aIndex < aLength; ++aIndex) {
		if (aMatch.at(aIndex)) {
			aPosition[positionIndex] = aIndex;
			++positionIndex;
		}
	}
			
	for (int bIndex(0), positionIndex(0); bIndex < bLength; ++bIndex) {
		if (bMatch.at(bIndex)) {
			bPosition[positionIndex] = bIndex;
			++positionIndex;
		}
	}
			
	// Counting half-transpositions.
	int transpositions(0);
	for (int index(0); index < matchingCharacters; ++index) {
		if (a.at(aPosition.at(index)) != b.at(bPosition.at(index))) {
			++transpositions;
		}
	}
			
	// Calculate Jaro distance.
	return (
		JARO_WEIGHT_STRING_A * matchingCharacters / aLength +
		JARO_WEIGHT_STRING_B * matchingCharacters / bLength +
		JARO_WEIGHT_TRANSPOSITIONS * (matchingCharacters - transpositions / 2) / matchingCharacters
	);
}

double Alpaga::Distance::jaroWinkler(const std::string &&a, const std::string &&b) {
	return jaroWinkler(a, b);
}

double Alpaga::Distance::jaroWinkler(const std::string &a, const std::string &b) {
	double distance(jaroDistance(a, b));
			
	if (distance > JARO_WINKLER_BOOST_THRESHOLD) {
		int commonPrefix(0);
		for (int index(0), indexEnd(std::min(std::min(static_cast<int>(a.size()), static_cast<int>(b.size())), JARO_WINKLER_PREFIX_SIZE)); index < indexEnd; ++index) {
			if (a.at(index) == b.at(index))
				++commonPrefix;
			else
				break;
			distance += JARO_WINKLER_SCALING_FACTOR * commonPrefix * (1.0 - distance);
		}
	}
		
	return distance;
}