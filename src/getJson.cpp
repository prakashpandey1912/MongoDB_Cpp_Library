#include "mongocpp.h"
using namespace std;
int main()
{
MongoClient *mongoClient=new MongoClient("mongodb://localhost:27017");
DBCollection *Collection=mongoClient->getCollection("tmdb","prakash");
BasicDBObjectBuilder *queryBuilder=new BasicDBObjectBuilder();
DBCursor *cursor=Collection->find();
while(cursor->hasNext())
{
cout<<cursor->next()<<endl;
}
delete cursor;
delete queryBuilder;
delete mongoClient;
cout<<"done";
return 0;
}