#include <stdio.h>
#include <stdlib.h>
#define LEN 19901  //想定される最多の交点数

typedef struct{
  double x;
  double y;
  int a;
  int b;
  int count;
}Point;

Point find_intersection(Point *p,int N,Point L1,Point L2){
  Point res;
  int i;
  double a,s,t,maxx=0,maxy=0;
  //L1.aとL1.bの座標を結ぶ線分をL1とする
  L1.a-=1;
  L1.b-=1;
  L2.a-=1;
  L2.b-=1;
  a = (p[L1.b].y-p[L1.a].y)*(p[L2.b].x-p[L2.a].x)-(p[L1.b].x-p[L1.a].x)*(p[L2.b].y-p[L2.a].y);
  if(a == 0) res.x = -1;
  else{
    s = (p[L2.a].x-p[L1.a].x)/a;
    t = (p[L2.a].y-p[L1.a].y)/a;
    if(s >= 0 && s <= 1 && t >= 0 && t <= 1){
      res.x = ((p[L2.a].y*p[L2.b].x-p[L2.a].x*p[L2.b].y)*(p[L1.b].x-p[L1.a].x)-(p[L1.a].y*p[L1.b].x-p[L1.a].x*p[L1.b].y)*(p[L2.b].x-p[L2.a].x))/((p[L1.b].y-p[L1.a].y)*(p[L2.b].x-p[L2.a].x)-(p[L1.b].x-p[L1.a].x)*(p[L2.b].y-p[L2.a].y));
      res.y = ((p[L2.a].y*p[L2.b].x-p[L2.a].x*p[L2.b].y)*(p[L1.b].y-p[L1.a].y)-(p[L1.a].y*p[L1.b].x-p[L1.a].x*p[L1.b].y)*(p[L2.b].y-p[L2.a].y))/((p[L1.b].y-p[L1.a].y)*(p[L2.b].x-p[L2.a].x)-(p[L1.b].x-p[L1.a].x)*(p[L2.b].y-p[L2.a].y));
       }
    else res.x =-1;
  }
  for(i=0; i<N; i++){
    if(p[i].x==res.x&&p[i].y==res.y){
      res.x=-1;
      break;
    }
  }
  if(res.x!=-1) p[0].count++;
  return res;
}

Point* BubbleSort(Point* sort,int count){
  int i,j;
  double temp;

  for(i=0;i<count;i++){
    for(j=count-1;j>i;j--){
      if(sort[j].x<sort[j-1].x){
        temp=sort[j].x;
        sort[j].x=sort[j-1].x;
        sort[j-1].x=temp;
      }
      else if(sort[j].x==sort[i-j].x && sort[j].y<sort[j-1].y){ //もしxが同じならyで比較
        temp=sort[j].y;
        sort[j].y=sort[j-1].y;
        sort[j-1].y=temp;
      }
    }
  }
  return sort;
}

int main(){
  int N, M, P, Q, i,j;
  double x, y;
  Point *p, *o, sort[LEN], res;

  scanf("%d%d%d%d",&N, &M, &P, &Q);
  p=(Point*)malloc(N*sizeof(Point));
  o=(Point*)malloc((2*M)*sizeof(Point));  //動的配列にすることで3本以上の線分に対応
  for(i=0; i<N; i++)    scanf("%lf%lf",&p[i].x, &p[i].y);
  for(i=0; i<M; i++)    scanf("%d%d",&o[i].a, &o[i].b);
  p[0].count=0;     //交点を数えるためのカウンタ変数
  for(i=0; i<M-1; i++)  //ここのループ2つで2線分のすべての組み合わせを調べる
    for(j=i+1;j<M;j++){
      res=find_intersection(p,N,o[i],o[j]);
      if(res.x!=-1){  //交点が存在するとき、ソート用の配列にその座標をコピーする
	sort[p[0].count-1].x=res.x;
        sort[p[0].count-1].y=res.y;
      }
    }
  BubbleSort(sort,p[0].count);   //ソート
  for(i=0;i<p[0].count;i++) printf("%f,%f\n",sort[i].x sort[i].y);
  printf("\n");
  return 0;
}
