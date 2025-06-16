#ifndef OFFICEGENCLIENT_H
#define OFFICEGENCLIENT_H

#include "grpc++/grpc++.h"
#include "office.pb.h"
#include "office.grpc.pb.h"
#include "google/protobuf/empty.pb.h"

class GenerateClient
{
public:
    GenerateClient(std::shared_ptr<grpc::Channel> channel) : stub_(office::Generate::NewStub(channel)) {}
    office::DocInfoList getAvailableDocs() const {
        grpc::ClientContext context_;
        office::DocInfoList docInfoList;
        stub_->GetAvailableDocs(&context_, google::protobuf::Empty(), &docInfoList);
        return docInfoList;
    }

private:
    std::unique_ptr<office::Generate::Stub> stub_;
};

#endif // OFFICEGENCLIENT_H
