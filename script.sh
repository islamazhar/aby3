set -xe
rm -rf out
python3 build.py --setup
python3 build.py --  -DlibOTe_Dirs="./thirdparty/libOTe/"
#  Peter just added the -- demark. It was supposed to be send to cmake since Python3 can not understand it?
#  libOTeCmd = cmd + " -- -DENABLE_CIRCUITS=ON " + cmakePrefix;