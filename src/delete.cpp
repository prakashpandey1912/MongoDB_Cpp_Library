#include "mongocpp.h"
using namespace std;
int main()
{
MongoClient *mongoClient=new MongoClient("mongodb://localhost:27017");
DBCollection *Collection=mongoClient->getCollection("tmdb","prakash");
BasicDBObjectBuilder *objectBuilder=new BasicDBObjectBuilder();
objectBuilder->start();
objectBuilder->Append("_id",101);
DBObject *document=objectBuilder->get();
Collection->remove(document);
delete objectBuilder;
delete mongoClient;
cout<<"done";
return 0;
}