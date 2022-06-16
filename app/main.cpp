//
//  Copyright © 2022 Aaron Ridley, Arnaud Becheler, Aidan Kingwell. All rights reserved.
//

#include <boost/program_options.hpp>
#include <exception>

#include "options.h"
#include "utils.h"
// #include "hybridLambda.hpp"

namespace bpo = boost::program_options;

namespace
{
  const size_t ERROR_IN_COMMAND_LINE = 1;
  const size_t SUCCESS = 0;
  const size_t ERROR_UNHANDLED_EXCEPTION = 2;
}

int main(int argc, char* argv[])
{
  bpo::variables_map vm;
  bool verbose = false;
  try{
    vm = handle_options(argc, argv);
    // --help option
    if (vm.count("help") || vm.count("version") )
    {
      return SUCCESS;
    }
  }
  catch(boost::program_options::required_option& e)
  {
    std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
    return ERROR_IN_COMMAND_LINE;
  }
  catch(boost::program_options::error& e)
  {
    std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
    return ERROR_IN_COMMAND_LINE;
  }
  catch ( const std::exception& e )
  {
    std::cerr << e.what() << std::endl;
    return ERROR_IN_COMMAND_LINE;
  }
  // the following can run without fear because everything is required to be present

  // --verbose option
  if (vm.count("verbose"))
  {
    verbose = true;
    app::utils::PrintVariableMap(vm);
  }

  if(verbose){ std::cout << "Initialization" << std::endl; }

  // HybridLambda run_hybridLambda (vm, verbose);

  if(verbose){ std::cout << "Running ..." << std::endl; }

  try
  {
    // run_hybridLambda.HybridLambda_core( );
    // run_hybridLambda.create_site_data_dir();

    if(verbose){ std::cout << "Segregating site data were generated ..." << std::endl; }

    // run_hybridLambda.extract_tmrca ();
    // run_hybridLambda.extract_bl ();
    // run_hybridLambda.extract_firstcoal();
    // run_hybridLambda.extract_frequency();
  }

  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
