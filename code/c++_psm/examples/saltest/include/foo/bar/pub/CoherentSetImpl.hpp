#ifndef ORG_OPENSPLICE_PUB_COHERENT_SET_IMPL_HPP_
#define ORG_OPENSPLICE_PUB_COHERENT_SET_IMPL_HPP_

#include <iostream>

namespace org {
  namespace opensplice {
    namespace pub {
      class CoherentSetImpl;
    }
  }
}

/** @todo OSPL-1741 This doesn't seem to be doing anything.... */

class org::opensplice::pub::CoherentSetImpl {
public:
    CoherentSetImpl(const dds::pub::Publisher& t) : t_(t), ended_(false) {
        std::cout << "=== begin coherent changes ===" << std::endl;
    }
    void end() {
        if (!ended_) {
            std::cout << "=== end coherent changes ===" << std::endl;
            ended_ = true;
        }
    }
    ~CoherentSetImpl() {
        if (!ended_) {
            this->end();
        }
    }

private:
    dds::pub::Publisher t_;
    bool ended_;
};

#endif /* OMG_IDDS_PUB_COHERENT_SET_IMPL_HPP_ */
