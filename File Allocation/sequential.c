#include <stdio.h>
#include <string.h>

struct File {
    char name[20];
    int start_block,num_blocks;
};

int main(){
    int n;
    printf("Enter number of files: ");
    scanf("%d",&n);
    struct File files[n];
    for (int i=0;i<n;++i){
        printf("Enter file name: ");
        scanf("%s",files[i].name);
        printf("Enter start block: ");
        scanf("%d",&files[i].start_block);
        printf("Enter number of blocks: ");
        scanf("%d",&files[i].num_blocks);
    }
    printf("File Allocation Table:\n");
    printf("File Name\tStart Block\tLength\n");
    for (int i=0;i<n;++i){
        printf("%s\t%d\t%d\n",files[i].name,files[i].start_block,files[i].num_blocks);
    }
}
