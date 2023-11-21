#include "request_queue.h"

using namespace std;

RequestQueue::RequestQueue(const SearchServer& search_server) 
    : search_server_(search_server), no_result_requests_(0), time_(0) {
    }

vector<Document> RequestQueue::AddFindRequest(const string& raw_query, DocumentStatus status) {
    vector<Document> find_request = search_server_.FindTopDocuments(raw_query, status);
    UpdateRequestQueue(find_request.size());
    return find_request;
}

vector<Document> RequestQueue::AddFindRequest(const string& raw_query) {
    vector<Document> find_request = search_server_.FindTopDocuments(raw_query);
    UpdateRequestQueue(find_request.size());
    return find_request;
}

int RequestQueue::GetNoResultRequests() const {
    return no_result_requests_;
}

void RequestQueue::UpdateRequestQueue(int result) {
    ++time_;
    while (!requests_.empty() && min_in_day_ <= time_ - requests_.front().time) {
        if (0 == requests_.front().result) {
            --no_result_requests_;
        }
        requests_.pop_front();
    }
    requests_.push_back({result, time_});
    if (0 == result) {
        ++no_result_requests_;
    }
}