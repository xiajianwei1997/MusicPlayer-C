#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"link.h"        

int main(int argc, char const *argv[])
{
    //启动播放界面
    clear_screen();
    play_interface();
    cusor_hide();

    //播放歌曲
    int song_num;
    cusor_moveto(20,26);
    printf("请选择要播放的歌曲,输入1~4:");
    char song_list[8][32] = {"love.mp3","rainup.mp3","shbk.mp3","snow.mp3","love.lrc","rainup.lrc","shbk.lrc","snow.lrc"};
    scanf("%d",&song_num);
    mplayer_play(song_list[song_num-1]);
    
    //获取文件歌词
    char *song_lyrics;
    song_lyrics = get_song(song_list[song_num+3]);
        
    //按行切割歌词，指针数组保存各个行的首地址
    int row = 0;
    char *song[128] = {song_lyrics,NULL};
    get_song_lyrics(song,&row);

    //分析保存歌曲信息的行
    get_song_msg(song);

    //分析歌词正文，并插入链表
    SONG *head = NULL;
    head = get_every_lyrics(song,row,head);
     
    //模拟时钟，同步输出歌词、进度条
    analog_clock(head);

    return 0;
}

