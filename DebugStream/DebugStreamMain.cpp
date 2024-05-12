#include "DebugStream.h"




/////////////////////// Main ///////////////////////
int main() {
    dout << "Can print out string objects\n";
    dout << "Can print out int: " << 100 << endl;
    dout << "Can print out double: " << 1/3. << endl;
    
    dout << setprecision(2) << 0.0999 << " " << 0.9999 << " " << 0.2256 << endl;

    return 0;
}