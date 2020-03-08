#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define PAI 3.1415926
long long lef=-1,rig=2;
int M=50,GEN=10000,upb=32;
long long base=((long long)1)<<upb;
double vc=0.05,mc=0.7;
double total=0;
struct gene{
    long long data;
    double fitness;
}population[2][10000];
double expression(gene A){
    double loc=lef+((double)(rig-lef)*((double)A.data)/base);
    return 5-sin(10*PAI*loc)*loc;
}
gene variation(int num,int gen){
    gene temp;
    temp.data=(((long long)rand())<<17)|(rand()<<2)|(rand());
    temp.fitness=expression(temp);
    return temp;
}
gene mating(int p1,int p2,int gen){
    //if(population[gen][p1].fitness<population[gen][p2].fitness) swap(p1,p2);
    gene temp;
    temp.data=(population[gen][p1].data&4294901760)|(population[gen][p2].data&65535);
    temp.fitness=expression(temp);
    return temp;
}
int randomchoice(int gen){
    int INTE=rand()%((int)total+1),choice=0;
    double ans=INTE+((double)rand())/(0x7FFF);
    while(ans>0)
        ans-=population[gen][choice++].fitness;
    return MIN(choice,M-1);
}
int main(){
    freopen("text","w",stdout);
    srand((unsigned)time(NULL));
    for(int i=0;i<M;++i){
        population[0][i].data=(((long long)rand())<<17)|(rand()<<2)|(rand());
        population[0][i].fitness=expression(population[0][i]);
        total+=population[0][i].fitness;
    }
    double choice;
    for(int i=0;i<GEN;++i){
        int num=0;
        while(num<M){
            choice=((double)rand())/0x7FFF;
            if(choice<=vc){
                int index=rand()%M;
                population[(i+1)%2][num++]=variation(index,i%2);
                if( population[(i+1)%2][num-1].data<0){
                    printf("var fault");
                    return 0;
                }
            }
            else if(choice<=vc+mc){
                population[(i+1)%2][num++]=mating(randomchoice(i%2),randomchoice(i%2),i%2);
                if( population[(i+1)%2][num-1].data<0){
                    printf("mating fault");
                    return 0;
                }
                population[(i+1)%2][num++]=mating(randomchoice(i%2),randomchoice(i%2),i%2);
                if( population[(i+1)%2][num-1].data<0){
                    printf("mating fault");
                    return 0;
                }
            }
            else{
                int cpy=randomchoice(i%2);
                population[(i+1)%2][num++]=population[i%2][cpy];
            }
        }
        total=0;
        //printf("Generation : %d\n",i+1);
        if(i==9999)
        for(int j=0;j<M;++j){
            total+=population[(i+1)%2][j].fitness;
            double loc=lef+((double)(rig-lef)*((double)population[(i+1)%2][j].data)/base);
            printf("%lf ",loc);
        }
        //puts("");
    }
    return 0;
}
