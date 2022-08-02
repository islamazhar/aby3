
#include <cryptoTools/Common/CLP.h>

#include "aby3_tests/aby3_tests.h"
#include <tests_cryptoTools/UnitTests.h>
#include <aby3-ML/main-linear.h>
#include <aby3-ML/main-logistic.h>
#include <aby3-ML/main-pred.h>

#include "tests_cryptoTools/UnitTests.h"
#include "cryptoTools/Crypto/PRNG.h"

using namespace oc;
using namespace aby3;
std::vector<std::string> unitTestTag{ "u", "unitTest" };


void help()
{

	// TODO: Add more verbose help messages.
	std::cout << "-u                        ~~ to run all tests" << std::endl;
	std::cout << "-u n1 [n2 ...]            ~~ to run test n1, n2, ..." << std::endl;
	std::cout << "-u -list                  ~~ to list all tests" << std::endl;
}


int main(int argc, char** argv)
{


	try {


		bool set = false;
		oc::CLP cmd(argc, argv);


		if (cmd.isSet(unitTestTag))
		{
			auto tests = tests_cryptoTools::Tests;
			tests += aby3_tests;
			tests.runIf(cmd);
			return 0;
		}

		if (cmd.isSet("linear-plain"))
		{
			set = true;
			linear_plain_main(cmd);
		}
		if (cmd.isSet("linear"))
		{
			set = true;
			linear_main_3pc_sh(cmd);
		}

		if (cmd.isSet("logistic-plain"))
		{
			set = true;
			logistic_plain_main(cmd);
		}

		if (cmd.isSet("logistic"))
		{
			set = true;
			logistic_main_3pc_sh(cmd);
		}
		if(cmd.isSet("neural"))
		{
			set = true;
			neural_pred_main_3pc_sh(cmd);
		}


		if (set == false)
		{
			help();
		}

	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
