#include <string>
#include "document.h"

using namespace std;

Document::Document(int id, double relevance, int rating)
    : id(id)
    , relevance(relevance)
    , rating(rating) {
}

ostream& operator<<(ostream& out, const Document& document) {
    out << "{ document_id = "s << document.id;
    out << ", relevance = "s << document.relevance;
    out << ", rating = "s << document.rating << " }"s;
    return out;
}