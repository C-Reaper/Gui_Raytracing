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

    Raytracing_Add(
        &rt,
        (Raytracing_Object){
            .fn_hit = (char(*)(const struct Raytracing_Object* const,Raytracing_Hit* const,Vec3D,Vec3D))Raytracing_Sphere_Hit,
            .col = LIGHT_YELLOW,
            .light = 1.0f,
            .rs = Raytracing_Sphere_New(
                Vec3D_New(0.0f,0.0f,0.0f),
                10.0f
            )
        }
    );

    Raytracing_Add(
        &rt,
        (Raytracing_Object){
            .fn_hit = (char(*)(const struct Raytracing_Object* const,Raytracing_Hit* const,Vec3D,Vec3D))Raytracing_Plane_Hit,
            .col = GREEN,
            .light = 0.0f,
            .rp = Raytracing_Plane_New(
                Vec3D_New(0.0f,-5.0f,0.0f),
                Vec3D_New(0.0f,1.0f,0.0f)
            )
        }
    );

    Raytracing_Add(
        &rt,
        (Raytracing_Object){
            .fn_hit = (char(*)(const struct Raytracing_Object* const,Raytracing_Hit* const,Vec3D,Vec3D))Raytracing_AABox_Hit,
            .col = BLUE,
            .light = 0.0f,
            .raab = Raytracing_AABox_New(
                Vec3D_New(0.0f,2.0f,-4.0f),
                Vec3D_New(1.0f,1.0f,2.0f)
            )
        }
    );
    Raytracing_Add(
        &rt,
        (Raytracing_Object){
            .fn_hit = (char(*)(const struct Raytracing_Object* const,Raytracing_Hit* const,Vec3D,Vec3D))Raytracing_Disk_Hit,
            .col = RED,
            .light = 0.0f,
            .rd = Raytracing_Disk_New(
                Vec3D_New(2.0f,2.0f,-4.0f),
                Vec3D_New(0.0f,1.0f,0.0f),
                1.0f
            )
        }
    );
    Raytracing_Add(
        &rt,
        (Raytracing_Object){
            .fn_hit = (char(*)(const struct Raytracing_Object* const,Raytracing_Hit* const,Vec3D,Vec3D))Raytracing_Cylinder_Hit,
            .col = ORANGE,
            .light = 0.0f,
            .rc = Raytracing_Cylinder_New(
                Vec3D_New(8.0f,2.0f,-4.0f),
                1.0f
            )
        }
    );
    Raytracing_Add(
        &rt,
        (Raytracing_Object){
            .fn_hit = (char(*)(const struct Raytracing_Object* const,Raytracing_Hit* const,Vec3D,Vec3D))Raytracing_Cone_Hit,
            .col = BROWN,
            .light = 0.0f,
            .rcn = Raytracing_Cone_New(
                Vec3D_New(4.0f,4.0f,-4.0f),
                1.0f,
                2.0f
            )
        }
    );

    
    for(int i = 0;i<5;i++){
        for(int j = 0;j<5;j++){
            Raytracing_Add(
                &rt,
                (Raytracing_Object){
                    .fn_hit = (char(*)(const struct Raytracing_Object* const,Raytracing_Hit* const,Vec3D,Vec3D))Raytracing_Sphere_Hit,
                    .col = colors[
                            Random_u32_MinMax(
                                0U,
                                sizeof(colors) / sizeof(*colors)
                            )
                    ],
                    .light = 0.0f,
                    .rs = Raytracing_Sphere_New(
                        Vec3D_New(j * 2.0f,i * 2.0f,3.0f),
                        1.0f
                    )
                }
            );
        }
    }

    /*
    for(int i = 0;i<5;i++){
        for(int j = 0;j<5;j++){
            const int v = i + j % 2;
            
            Raytracing_Object ro = {
                .fn_hit = (
                    v == 0 ? (char(*)(const struct Raytracing_Object* const,Raytracing_Hit* const,Vec3D,Vec3D))Raytracing_Sphere_Hit : (
                    v == 1 ? (char(*)(const struct Raytracing_Object* const,Raytracing_Hit* const,Vec3D,Vec3D))Raytracing_AABox_Hit : (
                    v == 2 ? (char(*)(const struct Raytracing_Object* const,Raytracing_Hit* const,Vec3D,Vec3D))Raytracing_Plane_Hit : (
                             (char(*)(const struct Raytracing_Object* const,Raytracing_Hit* const,Vec3D,Vec3D))Raytracing_Disk_Hit
                )))),
                .col = colors[
                        Random_u32_MinMax(
                            0U,
                            sizeof(colors) / sizeof(*colors)
                        )
                ],
                .light = 0.0f,
                
            };

            if(v == 0)
                ro.rs = Raytracing_Sphere_New(
                    Vec3D_New(j * 2.0f,i * 2.0f,3.0f),
                    1.0f
                );
            else if(v == 1)
               ro.raab = Raytracing_AABox_New(
                    Vec3D_New(j * 2.0f,i * 2.0f,3.0f),
                    Vec3D_New(1.0f,1.0f,2.0f)
                );
            else if(v == 2)
                ro.rp = Raytracing_Plane_New(
                    Vec3D_New(j * 2.0f,i * 2.0f,3.0f),
                    Vec3D_New(0.0f,0.0f,-1.0f)
                );
            else
                ro.rd = Raytracing_Disk_New(
                    Vec3D_New(j * 2.0f,i * 2.0f,3.0f),
                    Vec3D_New(1.0f,1.0f,0.0f)
                );

            Raytracing_Add(&rt,ro);
        }
    }
    */
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

    Raytracing_Update(&rt,w->ElapsedTime);
    Raytracing_Render(&rt);

    Sprite rt_sp = Sprite_By(rt.w,rt.h,rt.buffer);
    Sprite_Render(WINDOW_STD_ARGS,&rt_sp,0.0f,0.0f);
}
void Delete(AlxWindow* w){
    Raytracing_Free(&rt);
}

int main(){
    if(Create("Raytracing on Objects",900,500,2,2,Setup,Update,Delete))
        Start();
    return 0;
}