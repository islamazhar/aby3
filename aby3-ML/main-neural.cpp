#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>

#include <time.h>

#include <cryptoTools/Network/IOService.h>

#include <cryptoTools/Common/CLP.h>
#include <Eigen/Dense>

#include "aby3-ML/NeuralNetwork.h"

#include "aby3-ML/aby3ML.h"
#include "aby3-ML/PlainML.h"

using namespace std;
using namespace Eigen;
using namespace oc;

// NN 
// DD

namespace aby3
{

    int nn_main_3pc_sh(oc::CLP & cmd) 
    {
        // For testing time.
        // 1. given conv. params do the convolution 
        // 2. Given number of sigmoid do them.
        auto N = cmd.getManyOr<int>("N", { 10000 });
		auto D = cmd.getManyOr<int>("D", { 1000 });
		auto B = cmd.getManyOr<int>("B", { 128 });
		auto IT = cmd.getManyOr<int>("I", { 10000 });

        PRNG prng(toBlock(1));
        std::cout << " N = " << N << " D = " << D << " B " << B << " IT " << IT << std::endl;    
    }
    int nn_plain_main(oc::CLP& cmd)
    {

    }
}