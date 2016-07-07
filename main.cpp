#include <stdio.h>
#include <graphics.h>


int ini(void);
int game(void);

int ini(void)
{

    // ��ʼ�������С
	initgraph(809,500);
    // random��ʼ��
	randomize();
	setbkmode(TRANSPARENT);
    // ��ô��ھ��
 	HWND hWnd = getHWnd();
    // ʹ�� API �����޸Ĵ�������
	SetWindowText(hWnd, TEXT("Flappy 2048"));

    // ����ͼƬ����������loadingͼƬ
	PIMAGE loading=newimage();
	getimage(loading,"pic\\loading.png");
    // ��ʾͼƬ
	putimage(0,0,loading);

	// ����������ɫ�����壬���뷽ʽ������
    setcolor(BLACK);
	setfont(0,0,"΢���ź�");
    settextjustify(CENTER_TEXT, TOP_TEXT);
    xyprintf(404,470,"Copyright Flappy 2048 Group");
    // ͼƬ��ʾʱ��
	delay_ms(1500);
    // ���loadingͼƬ
	delimage(loading);
}

int game(void)
{
    // �������ʱ�䣬����߶ȣ�����λ�ã����Ӷ��
    int time = 0;
    int birdheight = 250;
    int a = 0, b = 0, c = 0, point = 0;
    int speed = 100;
    float v = 0.0;
    // �����ļ�ָ�룬�洢��߷���
    FILE *fp;
    int bestpoint;
    int x,y;
    // �������ӽṹ��
    struct post {
        int x;
        int h;
    }post[3];

    // ����ͼƬ����������ͼƬ
    PIMAGE background = newimage();
    PIMAGE bird = newimage();
    PIMAGE post_u = newimage();
    PIMAGE shadow = newimage();
    PIMAGE backgroundshadow = newimage();

    getimage(background,"pic\\background.png");
    getimage(bird,"pic\\bird.png");
    getimage(post_u,"pic\\post.png");
    getimage(shadow,"pic\\shadow.png");
    getimage(backgroundshadow,"pic\\backgroundshadow.png");

    while(1)
    {
        // ��ʼ������
        time = 0;
        birdheight = 200;
        point = 0;
        a = 0; b = 0; c = 0;
        v = 0;

        // ���ӵĳ�ʼλ��
        post[0].x = 500;
        post[1].x = 865;
        post[2].x = 1231;
        post[0].h = 14.5;


        fp=fopen("best.txt","r");
        fscanf(fp,"%d",&bestpoint);
        fclose(fp);
        while(1)
        {

            time += 1;

            // ���������̲������ı䷽���ٶ�
            if((time-b)>1&&(keystate(VK_LBUTTON)||keystate(VK_SPACE)))
            {
                v=-180;
                b=time;
            }
            // ���㷽���λ�ã��������䵽�±�Եʱ���ϵ���
            if(birdheight > 490 && v > 0 )
                v = -0.8*v;
            v+=9.8;
            birdheight+=((v*1.9)/speed);

            // ���ӵ��ƶ����������Ƴ����ʱ�����õ��Ҳ࣬�����������������ƶ�
			 for(c=0;c<3;c++)
			 {
 				post[c].x-=2;
 				if(post[c].x<=-107)
 					post[c].x=999;
				if(post[c].x==500 || post[c].x==501)
				{
					post[c].h=random(3)*122-230;
				}
 			}

            // ����������������ƶ�������λ��ʱ������1��ͬʱ��¼��߷���
			for(c=0;c<3;c++)
			{
				if(post[c].x==118 || post[c].x==119)
					point++;
			}

            if(bestpoint<point)
                bestpoint = point;


			// ��ʾͼ�񣬰��Ⱥ�˳�����ͼ��ͬʱ�ﵽ�ڵ�����ͼ���Ч��

			// ��ʾ����
			putimage(0,0,background);

            // ��ʾ����
			for(c=0;c<3;c++)
			{
				putimage_withalpha(NULL,post_u,post[c].x,post[c].h);
				putimage_withalpha(NULL,post_u,post[c].x,(post[c].h+487));
			}

            putimage_withalpha(NULL,backgroundshadow,0,0);

            // ������ɫ������Խ�ߣ��任��ɫ

            if(point >= 0 && point < 2)
            {
                getimage(bird,"pic\\bird2.png");
                speed = 100;
            }
            if(point >= 2 && point < 4)
            {
                getimage(bird,"pic\\bird4.png");
                speed = 102;
            }
            if(point >= 4 && point < 8)
            {
                getimage(bird,"pic\\bird8.png");
                speed = 104;
            }
            if(point >= 8 && point < 16)
            {
                getimage(bird,"pic\\bird16.png");
                speed = 106;
            }
            if(point >= 16 && point < 32)
            {
                getimage(bird,"pic\\bird32.png");
                speed = 108;
            }
            if(point >= 32 && point < 64)
            {
                getimage(bird,"pic\\bird64.png");
                speed = 110;
            }
            if(point >= 64 && point < 128)
            {
                getimage(bird,"pic\\bird128.png");
                speed = 112;
            }
            if(point >= 128 && point < 256)
            {
                getimage(bird,"pic\\bird256.png");
                speed = 114;
            }
            if(point >= 256 && point < 512)
            {
                getimage(bird,"pic\\bird512.png");
                speed = 116;
            }
            if(point >= 512 && point < 1024)
            {
                getimage(bird,"pic\\bird1024.png");
                speed = 118;
            }
            if(point >= 1024 && point < 2048)
            {
                getimage(bird,"pic\\bird2048.png");
                speed = 120;
            }

            // ��ʾ����
            putimage_withalpha(NULL,bird,14,birdheight);



            // ��ײ���

            if(post[0].x>=14&&post[0].x<=121&&(post[0].h>(birdheight-230)||(post[0].h+490)<birdheight+107))
 				point = 0;
		 	if(post[1].x>=14&&post[1].x<=121&&(post[1].h>(birdheight-230)||(post[1].h+490)<birdheight+107))
 				point = 0;
		 	if(post[2].x>=14&&post[2].x<=121&&(post[2].h>(birdheight-230)||(post[2].h+490)<birdheight+107))
 				point = 0;

			if(birdheight < -50 || birdheight > 393)
                point = 0;


            putimage(500,0,shadow);


            // ��ʾ����

			setcolor(EGERGB(119,110,101));
			setfont(60,0,"Arial Black"); // ��һ������Ϊ�߶ȡ��ڶ�������Ϊ��ȣ�0ΪĬ�ϱ���
			settextjustify(CENTER_TEXT, TOP_TEXT);
			xyprintf(654,40,"SCORE");
			xyprintf(654,100,"%d",point);
			xyprintf(654,190,"BEST");
			xyprintf(654,250,"%d",bestpoint);
			xyprintf(654,380,"RESET");
            xyprintf(66,birdheight+26,"%d",point);


            // �������������������reset���򣬷�������Ϊ��
            if(keystate(VK_LBUTTON))
            {
                mousepos(&x,&y);
                if(x>575&&x<740&&y>380&&y<430)
                    point = bestpoint = 0;
            }
            // �洢��ѳɼ�
            fp=fopen("best.txt","w");
            fprintf(fp,"%d",bestpoint);
            fclose(fp);
            delay_fps(speed);
        }
    }
}

int WinMain(void)
{
	ini();
	game();

	return 0;
}
