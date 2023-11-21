#pragma once
#include <deque>
#include <string>
#include <vector>
#include "search_server.h"

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);
    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate);
    std::vector<Document> AddFindRequest(const std::string& raw_query, DocumentStatus status);
    std::vector<Document> AddFindRequest(const std::string& raw_query);
    int GetNoResultRequests() const;
private:
    struct QueryResult {
        int result;
        int time;
    };
    std::deque<QueryResult> requests_;
    const SearchServer& search_server_;
    const static int min_in_day_ = 1440;
    int no_result_requests_;
    int time_;
    
    void UpdateRequestQueue(int result);
};

template <typename DocumentPredicate>
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query, DocumentPredicate document_predicate) {
    std::vector<Document> find_request = search_server_.FindTopDocuments(raw_query, document_predicate);
    UpdateRequestQueue(find_request.size());
    return find_request;
}