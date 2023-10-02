#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
#define MAX_BUCKECTS_SIZE 100
//键值对变量
typedef struct{
   int key;
   char *val;
}pair;
//哈希表结构体
typedef struct{
   pair *buckets[MAX_BUCKECTS_SIZE];
}hashMap;
//有效键值对容器(包含个数)
typedef struct{
   void *sets;
   int size;
}mapCap;
//创建哈希表
hashMap *create_hashmap()
{
   hashMap *map=malloc(sizeof(hashMap));
   for(int i=0;i<MAX_BUCKECTS_SIZE;i++)
   map->buckets[i]=NULL;
   return map;
}
//清除哈希表
void free_hashmap(hashMap **map)
{
   for(int i=0;i<MAX_BUCKECTS_SIZE;i++)
      free((*map)->buckets[i]);
   free(*map);
   *map=NULL;
}
//哈希函数
int hash_function(int key)
{
   return key%MAX_BUCKECTS_SIZE;
}
//添加键值对
void putItem(hashMap *map,const int key,const char *val)
{
   pair *p=malloc(sizeof(pair));
   p->key=key;
   p->val=malloc(strlen(val)+1);//注意这里不能用sizeof，否则得到的是指针的长度8（64位）
   strcpy(p->val,val);
   int index=hash_function(key);
   map->buckets[index]=p;
}
//删除键值对
void removeItem(hashMap *map,const int key)
{
   int index=hash_function(key);
   free(map->buckets[index]);
   map->buckets[index]=NULL;
}
//获取有效键值对
mapCap *map_get(hashMap *map)
{
   mapCap *mapcap=malloc(sizeof(mapCap));
   int size=0;
   for(int i=0;i<MAX_BUCKECTS_SIZE;i++)
   {
      if(map->buckets[i]!=NULL)size++;
   }
   pair *p=malloc(sizeof(pair)*size);
   for(int i=0,index=0;i<MAX_BUCKECTS_SIZE;i++)
   {
      if(map->buckets[i]!=NULL)
      {
         p[index].key=map->buckets[i]->key;
         p[index].val=malloc(strlen(map->buckets[i]->val)+1);
         strcpy(p[index].val,map->buckets[i]->val);
         index++;
      }
   }
   mapcap->sets=p;
   mapcap->size=size;
}
//获取所有键
mapCap *key_get(hashMap *map)
{
   mapCap *cap=malloc(sizeof(mapCap));
   int size=0;
   for(int i=0;i<MAX_BUCKECTS_SIZE;i++)if(map->buckets[i]!=NULL)size++;
   int *key=malloc(sizeof(int)*size);
   for(int i=0,index=0;i<MAX_BUCKECTS_SIZE;i++)
   {
      if(map->buckets[i]!=NULL)
         key[index++]=map->buckets[i]->key;
   }
   cap->sets=key;
   cap->size=size;
   return cap;
}
//获取所有值
mapCap *val_get(hashMap *map)
{
   mapCap *cap=malloc(sizeof(mapCap));
   int size=0;
   for(int i=0;i<MAX_BUCKECTS_SIZE;i++)if(map->buckets[i]!=NULL)size++;
   char **p=malloc(sizeof(char *)*size);
   for(int i=0,index=0;i<MAX_BUCKECTS_SIZE;i++)
      if(map->buckets[i]!=NULL)
      {
         p[index]=malloc(strlen(map->buckets[i]->val)+1);
         p[index]=map->buckets[i]->val;
         index++;
      }
   cap->sets=p;
   cap->size=size;
   return cap;
}
int main()
{
   hashMap *map=create_hashmap();
   //添加键值对
   putItem(map,11232,"小红");
   putItem(map,11367,"小华");
   putItem(map,11221,"小明");
   //获取全部有效键值对
   mapCap *cap1=map_get(map);
   pair *p1=(pair *)cap1->sets;
   printf("%s\n",p1[0].val);
   free(cap1->sets);
   //获取所有有效值
   mapCap *cap2=key_get(map);
   int *p2=(int *)cap2->sets;
   printf("%d\n",p2[1]);
   removeItem(map,11232);//移除元素
   free(cap2->sets);
   //更新移除元素后的键值对
   mapCap *cap3=map_get(map);
   free(cap3->sets);
   //获取所有键
   mapCap *cap4=val_get(map);
   char **p=(char **)cap4->sets;
   printf("%s\n",p[1]);
   free(cap4->sets);
   free_hashmap(&map);
   return 0;
}