#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include "set.h"

TEST_CASE( "< <char 3>, 3>", "[set]" ) {

	std::array<char, 3> a1 = {'a', 'a', 'a'};
	std::array<char, 3> a2 = {'b', 'b', 'b'};
	
	std::array<char, 3> a3 = {'c', 'c', 'c'};
	std::array<char, 3> a4 = {'d', 'd', 'd'};
	
	Set< std::array<char, 3> , 3> set;
	set.add(a1);
	set.add(a3);
	
	Set< std::array<char, 3> , 3> set2;
	set2.add(a2);
	set2.add(a4);
	
    REQUIRE( (set.array[0] > set2.array[0]) == false );		// {a a a} > {b b b} == (FALSE)
    REQUIRE( (set2.array[0] > set.array[0]) == true );		// {b b b} > {a a a} == (TRUE)
	
	REQUIRE( set.max() == a3 );
	REQUIRE( set.max() != a2 );
	REQUIRE( set2.max() != a1 );
	REQUIRE( set2.max() == a4 );
	
}

TEST_CASE( "< <char 5>, 5>", "[set]" ) {

	std::array<char, 5> a1 = {'a', 'b', 'c', 'd', 'e'};
	std::array<char, 5> a2 = {'b', 'c', 'd', 'e', 'f'};
	
	Set<std::array<char, 5>, 5> set;
	set.add(a1);
	
	Set<std::array<char, 5>, 5> set2;
	set2.add(a2);
	
    REQUIRE( (set.array[0] > set2.array[0]) == false );		// {a a a} > {b b b} == (FALSE)
    REQUIRE( (set2.array[0] > set.array[0]) == true );		// {b b b} > {a a a} == (TRUE)
	
	REQUIRE( set.max() == a1 );
	REQUIRE( set.max() != a2 );
	REQUIRE( set2.max() != a1 );
	REQUIRE( set2.max() == a2 );
	
}

TEST_CASE( "<char, 3>", "[set]" ) {
	Set<char, 3> set;
	REQUIRE( set.contains('a') == false );
	set.add('a');
    REQUIRE( set.contains('a') == true );
	set.remove('a');
    REQUIRE( set.contains('a') == false );
	set.add('a');
	set.add('b');
	set.add('c');
	set.add('d');
    REQUIRE( set.contains('d') == false );
	set.remove('c');
	set.add('d');
    REQUIRE( set.contains('d') == true );
    REQUIRE( set.max() == 'd' );
}

TEST_CASE( "<char, 10>", "[set]" ) {
	Set<char, 10> set;
	REQUIRE( set.contains('a') == false );
	set.add('a');
    REQUIRE( set.contains('a') == true );
	set.remove('a');
    REQUIRE( set.contains('a') == false );
	set.add('a');
	set.add('b');
	set.add('c');
	set.add('d');
	set.add('e');
	set.add('f');
	set.add('g');
	set.add('h');
	set.add('i');
	set.add('j');
	set.add('k');
    REQUIRE( set.contains('k') == false );
	set.remove('j');
	set.add('k');
    REQUIRE( set.contains('k') == true );
    REQUIRE( set.max() == 'k' );
}

TEST_CASE( "<int, 3>", "[set]" ) {
	Set<int, 3> set;
	REQUIRE( set.contains(0) == false );
	set.add(0);
    REQUIRE( set.contains(0) == true );
	set.remove(0);
    REQUIRE( set.contains(0) == false );
	set.add(0);
	set.add(1);
	set.add(2);
	set.add(3);
    REQUIRE( set.contains(3) == false );
	set.remove(2);
	set.add(3);
    REQUIRE( set.contains(3) == true );
    REQUIRE( set.max() == 3 );
}

TEST_CASE( "<int, 10>", "[set]" ) {
	Set<int, 10> set;
	REQUIRE( set.contains(0) == false );
	set.add(0);
    REQUIRE( set.contains(0) == true );
	set.remove(0);
    REQUIRE( set.contains(0) == false );
	set.add(0);
	set.add(1);
	set.add(2);
	set.add(3);
	set.add(4);
	set.add(5);
	set.add(6);
	set.add(7);
	set.add(8);
	set.add(9);
	set.add(10);
    REQUIRE( set.contains(10) == false );
	set.remove(9);
	set.add(10);
    REQUIRE( set.contains(10) == true );
    REQUIRE( set.max() == 10 );
}