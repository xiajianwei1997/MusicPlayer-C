#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"link.h"


//有序插入
SONG* insert_link(SONG *head, SONG tmp)
{

    SONG *pi = (SONG *)calloc(1,sizeof(SONG));
    *pi = tmp;
    pi->next = NULL;

    
    if(head == NULL)
    {
        head = pi;
        return head;
    }
    else
    {
        
        SONG *pf=head,*pb=head;
        while (pb->time < pi->time && pb->next != NULL)
        {
            pf = pb;
            pb = pb->next;
        }

        if(pb->time >= pi->time)
        {
            if(pb == head)
            {
                pi->next = head;
                head = pi;
                return head;
            }
            else
            {
                pf->next = pi;
                pi->next = pb;
            }
        }
        else
        {
            pb->next = pi;
        } 
    }
    return head;
}


void play_interface()
{
    cusor_moveto(18,1);
    set_fg_color(33);
    printf("$************************************************************************************************************************************************$");
    cusor_moveto(18,2);
    printf("$************************************************************************************************************************************************$");
    cusor_moveto(18,38);
    printf("$************************************************************************************************************************************************$");
    cusor_moveto(18,39);
    printf("$************************************************************************************************************************************************$");
    int side_wall_col = 3;
    for ( side_wall_col = 3; side_wall_col < 38; side_wall_col++)
    {
        cusor_moveto(18,side_wall_col);
        printf("$");
        cusor_moveto(163,side_wall_col);
        printf("$");
    }  
    set_fg_color(37);
    cusor_moveto(103,34);
    printf("<  @  >");
    cusor_moveto(57,32);
    printf("|");
    cusor_moveto(159,32);
    printf("|");
    cusor_moveto(57,31); 
    printf("_______________________________________________________________________________________________________");
    cusor_moveto(20,10);
    printf("   1.简单爱-周杰伦\n");
    cusor_moveto(20,12);
    printf("   2.清明雨上-许嵩\n");
    cusor_moveto(20,14);
    printf("   3.说好不哭-周杰伦\n");
    cusor_moveto(20,16);
    printf("   4.断桥残雪-许嵩\n");
    
}


//读取歌词文件  整个字符串
char *get_song(char song_list[32])
{
    FILE *fp = NULL;
    fp = fopen(song_list, "r");
    fseek(fp,0,2);
    int len = ftell(fp);
    rewind(fp);
    char *lrc=(char *)calloc(1,len+1);
    fread(lrc,len-1,1,fp);
    fclose(fp);

    return lrc;
}


//按照行切割歌词存入指针数组中
void get_song_lyrics(char *song[128],int *row)
{
    int i=0;
    while((song[i] = strtok(song[i], "\r\n")) && ++i);
    *row = i;
}


//处理歌词中包含歌曲信息的部分
void get_song_msg(char *song[128])
{
    int i=0;
    char type[32]="";
    char type1[4][32]={"歌名:" ,"作者:", "专辑:", "作曲:"};
    char msg[32]="";
    int a = 4;
    for(i=0;i<4;i++)
    {
        sscanf(song[i],"[%[^:]:%[^]]",type,msg);
        cusor_moveto(97,a);
        printf("%s",type1[i]);
        cusor_moveto(102,a);
        printf("%s",msg);
        a++;
    }
    cusor_moveto(96,8);
    printf("-------------");   
}


//分析歌词正文，并插入链表
SONG *get_every_lyrics(char *song[128],int row,SONG *head)
{
    int i=0;
    for(i=4;i<row;i++)
    {
        char *song_lrc = song[i];
        while(*song_lrc == '[')
            song_lrc += 10;
        
        char *time_lrc = song[i];
        while(*time_lrc == '[')
        {
            SONG tmp;
            int m = 0,s=0,ms = 0;
            sscanf(time_lrc,"[%d:%d:%d]", &m,&s,&ms);
            if(ms>50)
            {
                tmp.time = m*60+s+1;
            }
            else
            {    
                tmp.time = m*60+s;
            }
            
            strcpy(tmp.lrc, song_lrc );
           
            //将提取到的时间节点 有序插入链表
            
            head = insert_link(head,tmp);
            time_lrc += 10;
        }
    }
    
    return head;
}



void analog_clock(SONG *head)
{
    
    SONG *pb = head;
    int time = 0;
    int j = 0,k = 0;
    int sum = 100;

    while(1)
    {
        cusor_moveto(65,34);
        printf("%02d:%02d|04:13",time/60,time%60);
        fflush(stdout);
        if(time == 0)
        {
            cusor_moveto(90,10);
            printf("%s               ", pb->lrc);
            cusor_moveto(90,12);
            printf("%s               ", pb->next->lrc);
            cusor_moveto(90,14);
            printf("%s               ", pb->next->next->lrc);
            cusor_moveto(90,16);
            // set_fg_color(31);
            printf("%s               ", pb->next->next->next->lrc);
            cusor_moveto(90,18);
            // set_fg_color(37);
            printf("%s               ", pb->next->next->next->next->lrc);
            cusor_moveto(90,20);
            printf("%s               ", pb->next->next->next->next->next->lrc);
            cusor_moveto(90,22);
            printf("%s               ", pb->next->next->next->next->next->next->lrc);          
        }
        else if(time == pb->time)
        {
            cusor_moveto(90,10);
            set_fg_color(36);
            printf("%s               ", pb->lrc);
            set_fg_color(37);
            cusor_moveto(90,12);
            printf("%s               ", pb->next->lrc);
            cusor_moveto(90,14);
            printf("%s               ", pb->next->next->lrc);
            cusor_moveto(90,16);
                
            printf("%s               ", pb->next->next->next->lrc);
            cusor_moveto(90,18);
                
            printf("%s               ", pb->next->next->next->next->lrc);
            cusor_moveto(90,20);
            printf("%s               ", pb->next->next->next->next->next->lrc);
            cusor_moveto(90,22);
            printf("%s               ", pb->next->next->next->next->next->next->lrc);    
        }
        else if(time == pb->next->time)
        {
            cusor_moveto(90,10);
            printf("%s               ", pb->lrc);
            cusor_moveto(90,12);
            set_fg_color(36);
            printf("%s               ", pb->next->lrc);
            set_fg_color(37);
            cusor_moveto(90,14);
            printf("%s               ", pb->next->next->lrc);
            cusor_moveto(90,16);
            printf("%s               ", pb->next->next->next->lrc);
            cusor_moveto(90,18);
            printf("%s               ", pb->next->next->next->next->lrc);
            cusor_moveto(90,20);
            printf("%s               ", pb->next->next->next->next->next->lrc);
            cusor_moveto(90,22);
            printf("%s               ", pb->next->next->next->next->next->next->lrc); 
        }
        else if(time == pb->next->next->time)
        {
            cusor_moveto(90,10);
            printf("%s               ", pb->lrc);
            cusor_moveto(90,12);
            printf("%s               ", pb->next->lrc);
            cusor_moveto(90,14);
            set_fg_color(36);
            printf("%s               ", pb->next->next->lrc);
            cusor_moveto(90,16);
            set_fg_color(37);
            printf("%s               ", pb->next->next->next->lrc);
            cusor_moveto(90,18);
                
            printf("%s               ", pb->next->next->next->next->lrc);
            cusor_moveto(90,20);
            printf("%s               ", pb->next->next->next->next->next->lrc);
            cusor_moveto(90,22);
            printf("%s               ", pb->next->next->next->next->next->next->lrc);  
        }
        else if((time == pb->next->next->next->time)  && ( NULL != pb->next->next->next->next->next->next->next))
        {
            cusor_moveto(90,10);
            printf("%s               ", pb->lrc);
            cusor_moveto(90,12);
            printf("%s               ", pb->next->lrc);
            cusor_moveto(90,14);
            printf("%s               ", pb->next->next->lrc);
            cusor_moveto(90,16);
            set_fg_color(36);
            printf("%s               ", pb->next->next->next->lrc);
            cusor_moveto(90,18);
            set_fg_color(37);
            printf("%s               ", pb->next->next->next->next->lrc);
            cusor_moveto(90,20);
            printf("%s               ", pb->next->next->next->next->next->lrc);
            cusor_moveto(90,22);
            printf("%s               ", pb->next->next->next->next->next->next->lrc);
            //滚屏显示
            pb = pb->next; 
        } 
        else if(time == pb->next->next->next->next->time)
        {
            cusor_moveto(90,10);
            printf("%s               ", pb->lrc);
            cusor_moveto(90,12);
            printf("%s               ", pb->next->lrc);
            cusor_moveto(90,14);
            printf("%s               ", pb->next->next->lrc);
            cusor_moveto(90,16);
            printf("%s               ", pb->next->next->next->lrc);
            cusor_moveto(90,18);
            set_fg_color(36);
            printf("%s               ", pb->next->next->next->next->lrc);
            cusor_moveto(90,20);
            set_fg_color(37);
            printf("%s               ", pb->next->next->next->next->next->lrc);
            cusor_moveto(90,22);
           printf("%s               ", pb->next->next->next->next->next->next->lrc);
        }
        else if(time == pb->next->next->next->next->next->time)
        {
            cusor_moveto(90,10);
            printf("%s               ", pb->lrc);
            cusor_moveto(90,12);
            printf("%s               ", pb->next->lrc);
            cusor_moveto(90,14);
            printf("%s               ", pb->next->next->lrc);
            cusor_moveto(90,16);
            printf("%s               ", pb->next->next->next->lrc);
            cusor_moveto(90,18);
            
            printf("%s               ", pb->next->next->next->next->lrc);
            cusor_moveto(90,20);
            set_fg_color(36);
            printf("%s               ", pb->next->next->next->next->next->lrc);
            cusor_moveto(90,22);
            set_fg_color(37);
           printf("%s               ", pb->next->next->next->next->next->next->lrc);
        }
        else if(time == pb->next->next->next->next->next->next->time)
        {
            cusor_moveto(90,10);
            printf("%s               ", pb->lrc);
            cusor_moveto(90,12);
            printf("%s               ", pb->next->lrc);
            cusor_moveto(90,14);
            printf("%s               ", pb->next->next->lrc);
            cusor_moveto(90,16);
            printf("%s               ", pb->next->next->next->lrc);
            cusor_moveto(90,18);
            printf("%s               ", pb->next->next->next->next->lrc);
            cusor_moveto(90,20);
            printf("%s               ", pb->next->next->next->next->next->lrc);
            cusor_moveto(90,22);
            set_fg_color(36);
           printf("%s               ", pb->next->next->next->next->next->next->lrc);
           set_fg_color(37);
        }
     
        //进度条
        sum = ((time*4)/10);
        cusor_moveto(58,32);   
        for ( j = 0; j < sum; j++)
        {
            set_fg_color(36); 
            printf(">"); 
            set_fg_color(37);  
        }
        for (k = 0; k <= (100 - sum); k++)
        {   
            printf("_");
        }
        cusor_moveto(145,34);
        if(sum == 101)
        {
            sum -= 1;
        }
        printf("%d%%/100%%",sum);

        sleep(1);
        if(time< (pb->next->next->next->next->next->next->time+2))
            time++;
    }
}


void cusor_moveto(int x, int y)
{// ESC[y;xH
    printf("\033[%d;%dH",y,x);
    fflush(stdout);
} 

//保存光标位置
void cusor_get_pos(void)
{// ESC[s
    printf("\033[s");
    fflush(stdout);
} 

//恢复光标位置
void cusor_set_pos(void)
{// ESC[u
    printf("\033[u");
    fflush(stdout);
} 
void cusor_hide(void)
{
	printf("\033[?25l");
}
void cusor_chuxian(void)
{
	printf("\033[?25h");
}

//清屏
void clear_screen(void)
{// ESC[2J
    printf("\033[2J");
    fflush(stdout);
}

//设置前景颜色
void set_fg_color(int color)
{// ESC[#m
    printf("\033[%dm",color);
    fflush(stdout);
}

//设置背景颜色
void set_bg_color(int color)
{// ESC[#m
    printf("\033[%dm",(color+10));
    fflush(stdout);
}  


void mplayer_play(char * song_path)
{
	pid_t pid;
	pid=fork();
	if(pid<0)
	{
		perror("fork");
	}
	else if(pid==0)
	{
		close(1);
		close(2);
		execlp("mplayer","mplayer","-slave","-quiet",song_path,NULL);
		exit(0);
       
	}
	else
		;
}



  