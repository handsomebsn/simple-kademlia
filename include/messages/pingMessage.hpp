//
// Created by jestjest on 11/19/17.
//

#ifndef INC_244B_FINAL_PINGMESSAGE_HPP
#define INC_244B_FINAL_PINGMESSAGE_HPP

#include "messages/message.hpp"
#include <cereal/types/polymorphic.hpp>

namespace kdml {
    namespace net {

        class PingMessage : public Message {
        public:
            PingMessage(KademliaNodeInfo& src, KademliaNodeInfo& dest);

            void print(std::ostream&) const override;

            template<class Archive>
            void serialize(Archive& ar) {
                ar(src, dest);
            }

            template<class Archive>
            static void load_and_construct(Archive& ar, cereal::construct<PingMessage>& construct) {
                KademliaNodeInfo src;
                KademliaNodeInfo dest;
                ar(src, dest);
                construct(src, dest);
            }
        };
    }
}

CEREAL_REGISTER_TYPE(kdml::net::PingMessage);
CEREAL_REGISTER_POLYMORPHIC_RELATION(kdml::net::Message, kdml::net::PingMessage);

#endif //INC_244B_FINAL_PINGMESSAGE_HPP