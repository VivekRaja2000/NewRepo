#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
typedef struct IPAddress IPAddress;
typedef struct IPAddressByte0 IpAddressByte0;
typedef struct IPAddressByte1 IpAddressByte1;
typedef struct IPAddressByte2 IpAddressByte2;
typedef struct IPAddressByte3 IpAddressByte3;
typedef struct PacketRule PacketRule;
int toplevelcount=0;
IpAddressByte0** _ips=NULL;
struct IPAddressByte0
{
    short location;
    int count;
    IpAddressByte1** nextParts;
};
struct IPAddressByte1
{
    short location;
    int count;
    IpAddressByte2** nextParts;
};
struct IPAddressByte2
{
    short location;
    int count;
    IpAddressByte3** nextParts;
};
struct IPAddressByte3
{
    short location;
    int count;
    PacketRule* PacketRule;
};
struct PacketRule
{
    bool incoming;
    bool outgoing;
};
struct IPAddress
{
    short parts[4];
};
IpAddressByte0* isRootAvailable(short part)
{
    int i=0;
    for(i=0;i<toplevelcount;i++)
    {
        IpAddressByte0* value=*(_ips+i);
        if((value)->location==part)
            return value;
    }
    return NULL;
}
IpAddressByte1* isPart1Available(short part,IpAddressByte0* location)
{
    int i=0;
    for(i;i<location->count;i++)
    {
        IpAddressByte1* value=*(location->nextParts+i);
        if(value->location==part)
            return value;
    }
    return NULL;
}
IpAddressByte2* isPart2Available(short part,IpAddressByte1* location)
{
    int i=0;
    for(i;i<location->count;i++)
    {
        IpAddressByte2* value=*(location->nextParts+i);
        if(value->location==part)
            return value;
    }
    return NULL;
}
IpAddressByte3* isPart3Available(short part,IpAddressByte2* location)
{
    int i=0;
    for(i;i<location->count;i++)
    {
        IpAddressByte3* value=*(location->nextParts+i);
        if(value->location==part)
            return value;
    }
    return NULL;
}
inline PacketRule* GetRule(IpAddressByte3* location)
{
    return location->PacketRule;
}
inline bool IncomingStatus(PacketRule* rule)
{
    return rule->incoming;
}
inline bool OutGoingStatus(PacketRule* rule)
{
    return rule->outgoing;
}
IpAddressByte0** CreateFireWall(IPAddress address[], PacketRule rules[],int count)
{
    int i=0;
    for(i=0;i<count;i++)
    {
        IpAddressByte0* byte0=isRootAvailable(address->parts[0]);
        if(byte0==NULL)
        {
            realloc(_ips,sizeof(IpAddressByte0)*(1+toplevelcount));
            _ips[toplevelcount]=(IpAddressByte0*)malloc(sizeof(IpAddressByte0));
            _ips[toplevelcount]->count=0;
            _ips[toplevelcount]->location=address->parts[0];
            _ips[toplevelcount]->nextParts=NULL;
            byte0=_ips[toplevelcount];
            toplevelcount++;
        }
        IpAddressByte1* byte1=isPart1Available(address->parts[1],byte0);
        if(byte1==NULL)
        {
            int count=byte0->count;
            realloc(byte0->location,sizeof(IpAddressByte1)*(1+byte0->count));
            byte0->nextParts[count]=(IpAddressByte1*)malloc(sizeof(IpAddressByte1));
            byte0->nextParts[count]->count=0;
            byte0->nextParts[count]->nextParts=NULL;
            byte1=byte0->nextParts[count];
            byte0->count++;
        }
        IpAddressByte2* byte2=isPart2Available(address->parts[2],byte1);
        if(byte2==NULL)
        {
            int count=byte1->count;
            realloc(byte1->location,sizeof(IpAddressByte2)*(1+byte1->count));
            byte1->nextParts[count]=(IpAddressByte2*)malloc(sizeof(IpAddressByte2));
            byte1->nextParts[count]->count=0;
            byte1->nextParts[count]->nextParts=NULL;
            byte2=byte1->nextParts[count];
            byte1->count++;
        }
        IpAddressByte3* byte3=isPart3Available(address->parts[3],byte2);
        if(byte3==NULL)
        {
            int count=byte2->count;
            realloc(byte2->location,sizeof(IpAddressByte3)*(1+byte2->count));
            byte2->nextParts[count]=(IpAddressByte3*)malloc(sizeof(IpAddressByte3));
            byte2->nextParts[count]->count=0;
            byte2->nextParts[count]->PacketRule=NULL;
            byte3=byte2->nextParts[count];
            byte2->count++;
        }
        byte3->PacketRule=(PacketRule*)malloc(sizeof(PacketRule));
        byte3->PacketRule->incoming=rules[i].incoming;
        byte3->PacketRule->outgoing=rules[i].outgoing;
    }
    return _ips;
}
bool AllowIncoming(IPAddress address)
{
    IpAddressByte0* byte0=isRootAvailable(address.parts[0]);
    if(byte0==NULL)
        return false;
    IpAddressByte1* byte1=isPart1Available(address.parts[1],byte0);
    if(byte1==NULL)
        return false;
    IpAddressByte2* byte2=isPart2Available(address.parts[2],byte1);
    if(byte2==NULL)
        return false;
    IpAddressByte3* byte3=isPart3Available(address.parts[3],byte2);
    if(byte3==NULL)
        return false;
    return byte3->PacketRule->incoming;
}
bool AllowOutging(IPAddress address)
{
    IpAddressByte0* byte0=isRootAvailable(address.parts[0]);
    if(byte0==NULL)
        return false;
    IpAddressByte1* byte1=isPart1Available(address.parts[1],byte0);
    if(byte1==NULL)
        return false;
    IpAddressByte2* byte2=isPart2Available(address.parts[2],byte1);
    if(byte2==NULL)
        return false;
   IpAddressByte3* byte3=isPart3Available(address.parts[3],byte2);
    if(byte3==NULL)
        return false;
    return byte3->PacketRule->outgoing;
}
int main()
{
    IPAddress array[3];
    array[0].parts[0]=190;
    array[0].parts[1]=10;
    array[0].parts[2]=19;
    array[0].parts[3]=123;
    array[1].parts[0]=190;
    array[1].parts[1]=42;
    array[1].parts[2]=43;
    array[1].parts[3]=54;
    array[2].parts[0]=24;
    array[2].parts[1]=43;
    array[2].parts[2]=34;
    array[2].parts[3]=23;
    PacketRule rules[3];
    rules[0].incoming=false;
    rules[0].outgoing=true;
    rules[1].incoming=true;
    rules[1].outgoing=true;
    rules[2].incoming=true;
    rules[2].outgoing=false;
    CreateFireWall(array,rules,3);
}