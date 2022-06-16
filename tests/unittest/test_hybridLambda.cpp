/*
 * hybrid-Lambda is used to simulate gene trees given species network under
 * coalescent process.
 *
 * Copyright (C) 2010 -- 2014 Sha (Joe) Zhu
 *
 * This file is part of hybrid-Lambda.
 *
 * hybrid-Lambda is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#define BOOST_TEST_MODULE TestHybridLambda

#include <boost/test/unit_test.hpp>

#include "src/hybridLambda.hpp"
#include "src/sim_gt.hpp"

BOOST_AUTO_TEST_SUITE( assert_not_throws )

BOOST_AUTO_TEST_CASE( test_command_line_interface )
{
  char* argv1[] = { "hybrid-Lambda", "-spcu", "trees/7_tax_sp_nt1_para", "-seg", "-o", "blah", "-sim_mut_unit", "-sim_num_gener" };

  BOOST_CHECK_NO_THROW( HybridLambda( 8, argv1 ) );

  BOOST_CHECK_NO_THROW( HybridLambda( 7, argv1 ) );

  BOOST_CHECK_NO_THROW( HybridLambda( 6, argv1 ) );

  BOOST_CHECK_NO_THROW( HybridLambda( 4, argv1 ) );

  BOOST_CHECK_NO_THROW( HybridLambda( 3, argv1 ) );

  BOOST_CHECK_NO_THROW( HybridLambda( 5, argv1 ) , std::invalid_argument );

  BOOST_CHECK_NO_THROW( HybridLambda( 2, argv1 ) , std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( test_runner )
{
  //if p = 1: lambda_{b, b}  =  1,  and all other lambda_{b,k} are 0
  BOOST_ASSERT_EQUAL(1.0, testSubjectPtr->lambdaPsi(2, 2, 1) );

  //CPPUNIT_ASSERT_ASSERTION_FAIL( testSubjectPtr->lambdaPsi(2, 1, 1) ); // This should not happen, k should be always at least 2.
  //CPPUNIT_ASSERT_ASSERTION_FAIL( testSubjectPtr->lambdaPsi(2, 3, 1) );

  BOOST_ASSERT_EQUAL(1.0, testSubjectPtr->lambdaPsi(3, 3, 1) );

  BOOST_ASSERT_EQUAL(0.0, testSubjectPtr->lambdaPsi(3, 2, 1) );

  BOOST_ASSERT_EQUAL(1.0, testSubjectPtr->lambdaPsi(30, 30, 1) );

  BOOST_ASSERT_EQUAL(0.0, testSubjectPtr->lambdaPsi(30, 10, 1) );

  BOOST_ASSERT_EQUAL(0.0, testSubjectPtr->lambdaPsi(30, 3, 1) );

  BOOST_ASSERT_EQUAL(1.0, testSubjectPtr->lambdaPsi(100, 100, 1) );

  BOOST_ASSERT_EQUAL(0.0, testSubjectPtr->lambdaPsi(100, 99, 1) );

  BOOST_ASSERT_EQUAL(0.0, testSubjectPtr->lambdaPsi(100, 97, 1) );

  BOOST_ASSERT_EQUAL(0.0, testSubjectPtr->lambdaPsi(100, 93, 1) );

  //if  p = 0:  lambda_{b, 2} =  b*(b-1)/2, and all other lambda_{b,k} are 0
  BOOST_ASSERT_EQUAL(0.0, testSubjectPtr->lambdaPsi(3, 3, 0) );

  BOOST_ASSERT_EQUAL(3, (int)testSubjectPtr->lambdaPsi(3, 2, 0) );

  BOOST_ASSERT_EQUAL(0.0, testSubjectPtr->lambdaPsi(4, 4, 0) );

  BOOST_ASSERT_EQUAL(0.0, testSubjectPtr->lambdaPsi(4, 3, 0) );

  BOOST_ASSERT_EQUAL(6, (int)testSubjectPtr->lambdaPsi(4, 2, 0) );

  BOOST_ASSERT_EQUAL(0.0, testSubjectPtr->lambdaPsi(40, 40, 0) );

  BOOST_ASSERT_EQUAL(0.0, testSubjectPtr->lambdaPsi(40, 39, 0) );

  BOOST_ASSERT_EQUAL(0.0, testSubjectPtr->lambdaPsi(40, 20, 0) );

  BOOST_ASSERT_EQUAL(0.0, testSubjectPtr->lambdaPsi(40, 9, 0) );

  BOOST_ASSERT_EQUAL(780, (int)testSubjectPtr->lambdaPsi(40, 2, 0) );
}

BOOST_AUTO_TEST_SUITE_END()
