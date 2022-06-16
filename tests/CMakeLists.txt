###############################################################################
### Command Line interface test
###############################################################################

add_test(
  NAME test_help
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --help
)

add_test(
  NAME test_version
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --version
)

add_test(
  NAME test_basic_1
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --spcu "((1:1,2:1):1,3:2);" --print
)

add_test(
  NAME test_basic_2
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --spcu "((1:1,2:1):1,3:2);" --print
)

add_test(
  NAME test_seed_num_and_output
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --spcu "((1:1,2:1):1,3:2);" --num 3 --seed 2 -o example1
)

add_test(
  NAME test_mutation
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --spcu trees/4_tax_sp_nt1_para -o example2 --num 2 --mu 0.00003 --sim_mut_unit --sim_num_mut
)

add_test(
  NAME test_population
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --spcu "((1:1,2:1):1,3:2);" --num 100 --pop 25000 --sim_num_gener
)

add_test(
  NAME test_png_and_pop
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --spng "(A:50000,B:50000)r;" --pop "(A:50000,B:50000)r:40000;"
)

add_test(
  NAME test_S
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --spcu "((((A:1.1,B:1.1):2.1,a:2.2):1.1,13D:.2):.3,4:.3);" --S 2 4 3 6 5
)

add_test(
  NAME test_mm
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --spcu "(A:1,B:1)r;" --mm "(A:1.9,B:.2)r:2;" --S 3 4
)

add_test(
  NAME test_dot_branch
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --spcu trees/7_tax_sp_nt1_para --dot --branch
)

add_test(
  NAME test_gene
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --spcu trees/4_tax_sp1.tre --num 1000 -o GENE --f
)

add_test(
  NAME test_gene_coal_unit
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --gt GENE_coal_unit --f
)

add_test(
  NAME test_mu_num_mut
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --spcu "((1:1,2:1):1,3:2);" -o GENE --num 100 --mu 0.00003 --sim_num_mut
)

add_test(
  NAME test_mt_seg
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --mt GENE_num_mut --seg
)

add_test(
  NAME test_mono
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --spcu "(A:5,B:5)r;" --mono --num 100 --mm .1 --S 4 4
)

add_test(
  NAME test_issue_44_case_1
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --spcu "((t3:1.123916174,((t4:0.4459935601,((t13:0.02953586373,t7:0.02953586373)I1:0.2529580411,t6:0.2824939049)I2:0.1634996552)I3:0.6268849558,(((t10:0.2528263692,((t5:0.02957738207)H26#0.5164631303:0.2232489871)H24#0.9067618483:0.0)I4:0.1281591885,(((t1:0.02957738207,H26#0.5164631303:0.0)I5:0.2232489871,H24#0.9067618483:0.0)I6:0.1281591885)H20#0.662992664:0.0)I7:0.07706148448,(t12:0.3809855577,H20#0.662992664:0.0)I8:0.07706148448)I9:0.6148314737)I10:0.05103765815)I11:1.604201279,t8:2.728117453)I12;" --num 100 --seed 6724
)

add_test(
  NAME test_issue_44_case_2
  COMMAND ${PROJECT_BINARY_DIR}/app/hybridlambda --spcu "(((((t3:0.2637610952,t2:0.2637610952)I1:1.0912968362,(t5:0.2662054335)#H22:1.0888524979)I2:0.2211237452,((#H22:0.1800944633)#H15:1.017267664)#H14:0.1126141157)I3:0.08142212706,#H14:0.1940362428)I4:0.2476537071,(t4:0.4462998968,#H15:0.0)I5:1.458957614)I6;" --num 6400 --seed 1619 -o gt
)

###############################################################################
### UNIT TEST
###############################################################################

# Keep test files in a separate source directory called unit_test
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} unit_test/*.cpp)

# Run through each source
foreach(testSrc ${TEST_SRCS})
        # Extract the filename without an extension (NAME_WE)
        get_filename_component(testName ${testSrc} NAME_WE)

        # Add compile target
        add_executable(${testName} ${testSrc} ${version_file})

        # Link to Boost libraries AND your targets and dependencies
        target_link_libraries(${testName}
                              ${Boost_LIBRARIES}
                              )

        # I like to move testing apparies into a testBin directory
        set_target_properties(${testName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/build/testBin)

        target_include_directories(
          ${testName} PRIVATE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

        #Finally add it to test execution. Notice the WORKING_DIRECTORY and COMMAND
        add_test(NAME ${testName}
                 WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/app
                 COMMAND ${PROJECT_BINARY_DIR}/app/${testName} )

endforeach(testSrc)
