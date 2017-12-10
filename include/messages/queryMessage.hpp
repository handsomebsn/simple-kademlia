//
// Created by jestjest on 12/2/17.
//

#ifndef SIMPLE_KADEMLIA_QUERYMESSAGE_HPP
#define SIMPLE_KADEMLIA_QUERYMESSAGE_HPP

#include "message.hpp"


namespace kdml {
    namespace net {

        class QueryMessage : public Message {
        protected:
            mp::uint256_t id{};
            QueryType qtype{};
        public:
            explicit QueryMessage(mp::uint256_t id, uint32_t tid,
                                  QueryType type)
                    : Message(tid, MessageType::QUERY),
                      id(std::move(id)), qtype(type) {}

            QueryType getQueryType() const { return qtype; }

            template<class Archive>
            void save(Archive& ar) const {
                std::vector<unsigned char> idVec(32);
                mp::export_bits(id, std::back_inserter(idVec), 8);
                ar(cereal::base_class<Message>(this), qtype, idVec);
            }

            template<class Archive>
            void load(Archive& ar) {
                std::vector<unsigned char> idVec(32);
                ar(cereal::base_class<Message>(this), qtype, idVec);
                mp::import_bits(id, idVec.begin(), idVec.end());
            }
        };

    }
}

#endif //SIMPLE_KADEMLIA_QUERYMESSAGE_HPP
