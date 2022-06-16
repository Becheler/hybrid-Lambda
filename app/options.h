
// Copyright 2022 Arnaud Becheler    <arnaud.becheler@gmail.com>

/***********************************************************************                                                                         *
* This program is free software; you can redistribute it and/or modify *
* it under the terms of the GNU General Public License as published by *
* the Free Software Foundation; either version 2 of the License, or    *
* (at your option) any later version.                                  *
*                                                                      *
************************************************************************/

#ifndef __APP_OPTIONS_H_INCLUDED__
#define __APP_OPTIONS_H_INCLUDED__

#include <boost/program_options.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

namespace bpo = boost::program_options;

///
/// @brief Returns a map with the program options
///
auto handle_options(int argc, char* argv[])
{
  // Declare a group of options that will be allowed only on command line
  bpo::options_description generic_options{"Command-line-only options"};
  generic_options.add_options()
  ("help,h", "help screen")
  ("verbose,v", "verbose mode")
  ("version", "software version")
  ("config", bpo::value<std::string>()->required(), "configuration file")
  ;
  // Allowed both on command line and in config file
  bpo::options_description model_options{"Model parameters"};
  model_options.add_options()
  ("spcu", bpo::value<std::string>(), "Input the species network/tree string through command line or a file. Branch lengths of the INPUT are in coalescent unit.")
  ("spng", bpo::value<std::string>(), "Input the species network/tree string through command line or a file. Branch lengths of the INPUT are in number of generation.")
  ("pop", bpo::value<double>()->default_value(10000), "Population sizes are defined by a single numerical constant,or a string which specifies thebpopulation size on each branch. The string can be input through command line or a file. By default, population size 10,000 is used.")
  ("mm", bpo::value<int>(), "Multiple merger parameters are defined by a single numerical constant. or a string which speifies the parameter on each branch. The string can be input through command line or a file. By default, Kingman coalescent is used.")
  ("S",bpo::value<std::vector<int> >()->multitoken(), "Specify the number of samples for each taxon.")
  ("num", bpo::value<int>(), "The number of gene trees will be simulated.")
  ("seed", bpo::value<int>(), "User define random SEED.")
  ("mu", bpo::value<double>()->default_value(0.00005), "User defined constant mutation rate per locus. By default mutation rate 0.00005 is used.")
  ("output,o", bpo::value<std::string>()->default_value("OUT"), "Specify the file name prefix for simulated gene trees. Prefix is set as \"OUT\" by default.")

  // Flags
  // When options are not specified, only output trees with branch lengths are in coalescent unit.
  ("sim_mut_unit", "Convert the simulated gene tree branch lengths to mutation unit.")
  ("sim_num_gener", "Convert the simulated gene tree branch lengths to number of generations.")
  ("sim_num_mut", "Simulate numbers of mutations on each branch of simulated gene trees.")
  ("sim_Si_num", "Generate a table, which includes the number of segregating sites and the total branch length of the gene tree, as well as the TMRCA.")
  //
  ("f", "Generate a topology frequency table of a set of input trees or simulated gene trees.")
  ("gt", bpo::value<std::string>(), "Specify the FILE NAME of trees to analyse tree topology frequencies.")
  //
  ("seg", "Generate segregating site data.")
  ("mt", bpo::value<std::string>(), "Specify the FILE NAME of trees to generate segregating site data.")
  // Tree branch lengths indicate number of mutations on the branch.
  ("mono", "Generate a frequency table of monophyletic, paraphyletic and polyphyletic trees.")
  ("spcu", bpo::value<std::string>(), "Input the species network/tree string through command line or a file. Branch lengths of the INPUT are in coalescent unit.")
  ;
  //
  bpo::options_description plot_options{"Plotting options"};
  plot_options.add_options()
  ("plot", "Use LaTEX(-plot) to draw the input (defined by -spcu) network(tree).")
  ("dot", "Use Dot (-dot) to draw the input (defined by -spcu) network(tree).")
  ("branch", "Branch lengths will be labelled in the figure.")
;
  bpo::options_description command_line_options;
  command_line_options.add(generic_options).add(model_options).add(plot_options);

  bpo::options_description file_options{"General options (command line values will overwrite config file values)"};
  file_options.add(model_options).add(plot_options);

  bpo::variables_map vm;

  try
  {

    bpo::store(
      bpo::command_line_parser(argc, argv).
      options(command_line_options).
      run(), vm); // can throw

    // --help option
    if (vm.count("help"))
    {
      std::cout << "--------------------------------------------------------------------------------------" << std::endl;
      std::cout << "| This is HYBRID LAMBDA reimplemented                                                 |" << std::endl;
      std::cout << "|   - Purpose: Do phylogenetic network stuff                                          |" << std::endl;
      std::cout << "|   - Author: Arnaud Becheler forked 2022;                                            |" << std::endl;
      std::cout << "|   - Usage: " << argv[0] << " [options] <config> ...                                 |" << std::endl;
      std::cout << "--------------------------------------------------------------------------------------|" << std::endl;
      std::cout << "\n" << generic_options << std::endl;
      std::cout << "\n" << file_options << std::endl;
      return vm;
      // SUCCESS
    }
    // --version option
    if (vm.count("version"))
    {
      std::cout << "Hybrid Lambda version 0.1" << std::endl;
      return vm;
      // SUCCESS
    }
    bpo::notify(vm); // throws on error, so do after help in case there are any problems
  }
  catch(boost::program_options::required_option& e)
  {
    throw;
  }
  catch(boost::program_options::error& e)
  {
    throw;
  }
  if (vm.count("config"))
  {
    std::ifstream ifs{vm["config"].as<std::string>().c_str()};
    if (ifs){
      store(parse_config_file(ifs, file_options), vm);
    }
  }
  notify(vm);
  return vm;
} // end of handle_options

#endif
