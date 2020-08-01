#include "mongocpp.h"
using namespace std;
int main()
{
MongoClient *mongoClient;
mongoClient=new MongoClient("mongodb://localhost:27017");
DBCollection *Collection=mongoClient->getCollection("tmdb","prakash");
BasicDBObjectBuilder *objectBuilder=new BasicDBObjectBuilder();
objectBuilder->start();
objectBuilder->Append("_id",101);
objectBuilder->Append("firstName","Prakash");
objectBuilder->Append("lastName","Pandey");
DBObject *document=objectBuilder->get();
Collection->insert(document);
delete objectBuilder;
delete mongoClient;
cout<<"done";
return 0;
}