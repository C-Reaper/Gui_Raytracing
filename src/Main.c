#include "/home/codeleaded/System/Static/Library/WindowEngine.h"
#include "/home/codeleaded/System/Static/Library/Raytracing.h"
#include "/home/codeleaded/System/Static/Library/Random.h"

int Menu = 0;
float Speed = 10.0f;
Raytracing rt;

void Menu_Set(int m){
	if(Menu==0 && m==1){
		AlxWindow_Mouse_SetInvisible(&window);
		SetMouse((Vec2){ GetWidth() / 2,GetHeight() / 2 });
	}
	if(Menu==1 && m==0){
		AlxWindow_Mouse_SetVisible(&window);
	}
	
	Menu = m;
}

void Setup(AlxWindow* w){
	Menu_Set(1);

    rt = Raytracing_New(
        GetWidth(),
        GetHeight(),
        Camera_Make(
            Vec3D_New(0.0f,0.0f,0.0f),
            Vec3D_New(3.14 * 0.25f,0.0f,0.0f),
            90.0f
        )
    );

    //Raytracing_Add(&rt,(Raytracing_Sphere[]){ Raytracing_Sphere_New(BLUE,Vec3D_New(-2.0f,0.0f,3.0f),1.0f)});
    //Raytracing_Add(&rt,(Raytracing_Sphere[]){ Raytracing_Sphere_New(RED,Vec3D_New(0.0f,0.0f,3.0f),1.0f)});
    //Raytracing_Add(&rt,(Raytracing_Sphere[]){ Raytracing_Sphere_New(YELLOW,Vec3D_New(2.0f,0.0f,3.0f),1.0f)});
    //Raytracing_Add(&rt,(Raytracing_Sphere[]){ Raytracing_Sphere_New(ORANGE,Vec3D_New(0.0f,-2.0f,3.0f),1.0f)});
    //Raytracing_Add(&rt,(Raytracing_Sphere[]){ Raytracing_Sphere_New(GREEN,Vec3D_New(0.0f,2.0f,3.0f),1.0f)});

    Pixel colors[] = {
        BLUE,
        RED,
        YELLOW,
        ORANGE,
        GREEN
    };

    for(int i = 0;i<5;i++){
        for(int j = 0;j<5;j++){
            Raytracing_Add(
                &rt,
                (Raytracing_Sphere[]){
                    Raytracing_Sphere_New(
                        colors[
                            Random_u32_MinMax(
                                0U,
                                sizeof(colors) / sizeof(*colors)
                            )
                        ],
                        Vec3D_New(j * 2.0f,i * 2.0f,3.0f),
                        1.0f
                    )
                }
            );
        }
    }
}
void Update(AlxWindow* w){
    if(Menu==1){
		Camera_Focus_S(&rt.cam,GetMouseBefore(),GetMouse(),GetScreenRect().d,1.0f);
		Camera_Update(&rt.cam);
		SetMouse((Vec2){ GetWidth() / 2,GetHeight() / 2 });
	}

    if(rt.w != GetWidth() || rt.h != GetHeight())
        Raytracing_Resize(&rt,GetWidth(),GetHeight());
	
	if(Stroke(ALX_KEY_ESC).PRESSED)
		Menu_Set(!Menu);
	
	if(Stroke(ALX_KEY_W).DOWN)
		rt.cam.p = Vec3D_Add(rt.cam.p,Vec3D_Mul(Vec3D_New(-rt.cam.fd.x,0.0f,rt.cam.fd.z),Speed * w->ElapsedTime));
	if(Stroke(ALX_KEY_S).DOWN)
		rt.cam.p = Vec3D_Sub(rt.cam.p,Vec3D_Mul(Vec3D_New(-rt.cam.fd.x,0.0f,rt.cam.fd.z),Speed * w->ElapsedTime));
	if(Stroke(ALX_KEY_A).DOWN)
		rt.cam.p = Vec3D_Sub(rt.cam.p,Vec3D_Mul(Vec3D_New(rt.cam.sd.x,0.0f,-rt.cam.sd.z),Speed * w->ElapsedTime));
	if(Stroke(ALX_KEY_D).DOWN)
		rt.cam.p = Vec3D_Add(rt.cam.p,Vec3D_Mul(Vec3D_New(rt.cam.sd.x,0.0f,-rt.cam.sd.z),Speed * w->ElapsedTime));
	if(Stroke(ALX_KEY_R).DOWN)
		rt.cam.p.y += Speed * w->ElapsedTime;
	if(Stroke(ALX_KEY_F).DOWN)
		rt.cam.p.y -= Speed * w->ElapsedTime;

    Raytracing_Render(&rt);

    Sprite rt_sp = Sprite_By(rt.w,rt.h,rt.buffer);
    Sprite_Render(WINDOW_STD_ARGS,&rt_sp,0.0f,0.0f);
}
void Delete(AlxWindow* w){
    Raytracing_Free(&rt);
}

int main(){
    if(Create("Raytracing on Objects",450,250,4,4,Setup,Update,Delete))
        Start();
    return 0;
}