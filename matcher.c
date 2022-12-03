#include "matcher.h"

/**
 * Your helper functions can go below this line
 */

/**
 * This is called on when the current char of the pattern that
 * is being checked is a '+'. It calls on itself until it reaches
 * a char in the line  that is not the same as that which preceded
 * the + in the pattern and returns the address where this unique
 * char is located.
 */
char* is_plus_operator(char *partial_line, char repeating_char) {
    if (*partial_line == repeating_char) {
	return is_plus_operator(partial_line + 1, repeating_char);
    }

    return partial_line;
}

/**
 * is_question_operator will be used when the next char in the 
 * pattern is a '?'. For the case where the preceding char does
 * appear in the line, the address of the next char in the line
 * is then returned. Otherwise, it simply returns the same address
 * that was passed as this char will still need to be checked with
 * the char in the pattern that appears after the ?.
 */
char* is_question_operator(char *partial_line, char *pattern) {
    if (*partial_line == *pattern) {
	return partial_line + 1;
    }
    else {
	return partial_line;
    }
}
/**
 * Your helper functions can go above this line
 */


/**
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
    /**
    * If the pattern is '\0' from the jump, then the line must
    * contain it as each one ends with the null terminator. On
    * the other hand, the way the function is implemented, if we
    * have reached the end of the pattern and haven't returned
    * 0 yet, that must mean a match was found and it should return
    * 1. So, either way 1 should be returned for '\0' being reached
    * in the pattern.  
    */
    if (*pattern == 0) {
        return 1;
    }

    /**
    * If the line has reached the null terminator, but the pattern hasn't,
    * that must mean we reached the end of the line before even getting 
    * through the full pattern so there must not be a match and it returns 0.
    */
    if (*partial_line == 0) {
        return 0;
    }

    /**
    * If the pattern is at a '\' (which needs to be put as '\\' to be properly
    * interpreted here), 0 will be returned if the current char of the line 
    * does not match the one that comes after the \ in the pattern. If they 
    * do match, the function will continue by calling itself with the next
    * char of the line and the char of the pattern that comes after the char
    * that proceeded the \.
    */
    if (*pattern == '\\') {
	if (*partial_line != *(pattern + 1)) {
	    return 0;
	}
	else {
	    return matches_leading(partial_line + 1, pattern + 2);
	}
    }

    /**
    * If the pattern is at a period, any char of the line will match so
    * it can just move by calling itself with the next char of each of the
    * line and pattern.
    */
    if (*pattern == '.') {
	return matches_leading(partial_line + 1, pattern + 1);
    }

    /**
    * If the next char of the pattern will be a '?', we run it by the 
    * is_question_operator function. At this point, the pattern should
    * be at the char two further down from the initial, past the ?, and 
    * partial_line was handled with the function. Can now move on by calling
    * itself.
    */
    if (*(pattern + 1) == '?') {
	partial_line  = is_question_operator(partial_line, pattern);
	pattern = pattern + 2;
	return matches_leading(partial_line, pattern);
    }

    /**
    * If the pattern is currently at a '+', is_plus_operator is ran from what
    * the pattern had before the +. Function then calls itself at the new point
    * of the line and pattern starting after the +.
    */
    if (*pattern == '+') {
	partial_line = is_plus_operator(partial_line, *(pattern - 1));
	return matches_leading(partial_line, pattern + 1);
    }

    /**
    * If the current char of the line is not equivalent to that of the pattern,
    * of course returns 0.
    */
    if (*partial_line != *pattern) {
        return 0;
    }

    /**
    * This point is reached when there wasn't a special case to handle or a mismatch.
    * Moves the function on with the next char of the line and pattern.
    */    
    return  matches_leading(partial_line + 1, pattern + 1);
}

/**
 * Implementation of your matcher function, which
 * will be called by the main program.
 *
 * You may assume that both line and pattern point
 * to reasonably short, null-terminated strings.
 */
int rgrep_matches(char *line, char *pattern) {
    /**
    * If the first call of matches_leading returns 1 (true), then a match has already
    * been found and this function can return true.
    */
    if (matches_leading(line, pattern)) {
	return 1;
    }

    /**
    * Otherwise, if not yet at the end of the line, compare the partial line that starts
    * from the next char of the line with the pattern by calling the function itself with 
    * this new point of the line.
    */
    if (*line != 0) {
	return rgrep_matches(line + 1, pattern);
    }

    /**
    * If the line has reached the end and 1 has not been returned, the pattern must've been
    * nowhere to be found and 0 is returned.
    */
    return 0;
}
