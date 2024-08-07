#include <stdio.h>
#include<stdlib.h>

struct File{
    int start,length,num,*blocks;
};

int main(){
    int n;
    printf("Enter number of files to be added: ");
    scanf("%d",&n);
    struct File files[n];
    for (int i=0;i<n;++i){
        printf("Enter start address, length, and number of files in block: ");
        scanf("%d %d %d",&files[i].start,&files[i].length,&files[i].num);
        files[i].blocks = malloc(files[i].num*sizeof(int));
        printf("Enter blocks: ");
        for (int j=0;j<files[i].num;++j){
            scanf("%d",files[i].blocks+j);
        }
    }
    int current;
    printf("Allocation table:\n");
    printf("File No\tNo of Blocks\tLength\tStart Address\n");
    for (int i=0;i<n;++i){
        printf("%d\t%d\t%d\n",i,files[i].num,files[i].length,files[i].start);
    }
    while (1){
        printf("1.Get the blocks\n");
        printf("2.Exit\n");
        scanf("%d",&current);
        if (current==1){
            printf("Enter file number: ");
            int fn;
            scanf("%d",&fn);
            for (int i=0;i<files[fn].num;++i){
                printf("%d ",files[fn].blocks[i]);
            }
            printf("\n");
        } else if (current==2){
            return 0;
        } else {
             printf("Enter valid input\n");
        }
    }
}
