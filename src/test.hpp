#ifndef test_h
#define test_h

#include <CakeEngine/CakeEngine.hpp>




Int func(void* arg){
	while(true){
		//std::cout << "From other thread!" << std::endl;
	}
	return 0;
}

void test(){
	/*
	CKReader *reader = CKReader::createFromFile("model.dae");
	CKXml::Object *data = CKXml::Decoder::decodeFrom(reader);
	reader->close();
	delete reader;
	CKWriter *writer = CKWriter::createToFile("saida.xml");
	CKXml::Encoder::encodeTo(writer, data);
	writer->close();
	delete writer;
	*/
}


class TestCore:public CKCore{
	
	CKModelBuilder *modelb;
	CKModelInstance *model;
	
	CKSpeaker *speaker;
	CKAudio *musica;
	CKAudio *musica2;
	
	CKThread *tr;
	CKImage *image;
	CKImage *image2;
	CKImage *image3;
	CKTexture *tex;
	CKTexture *tex2;
	CKTexture *tex3;
	CKFrameBuffer *fb;
	Int ww, wh;
	CKPov3D *cam;
	CKMat3 mat;
	
	void e_init(){
		
		musica = new CKAudio("mp.wav");
		musica2 = new CKAudio(musica->getBuffer());
		
		speaker = new CKSpeaker(window);
		speaker->play(musica);
		
		/* Core Scene Setup */
		
		//CKScene3D *scene = new CKScene3D();
		//this->scene3d = scene;
		
		CKReader *file = CKReader::createFromFile("suzan.dae");
		this->scene3d = CKDaeImporter::import(file);
		file->close();
		delete file;
		
		enabled_2dmode = true;
		enabled_3dmode = true;
		
		/* Model setup */
		
		modelb = new CKModelBuilder();
		CKModelMaterial *material1 = modelb->getMaterial();
		CKMeshBuilder *builder1 = modelb->getMeshBuilder();
		
		builder1->addVertex();
		builder1->setAttrib3v<Float>(material1->a_position, -0.25, +0.25, -1.5f);
		builder1->setAttrib3v<Float>(material1->a_normal, 0, 0, 1);
		builder1->setAttrib3v<Float>(material1->a_color, 1, 1, 1);
		builder1->setAttrib2v<Float>(material1->a_tex0uv, 0, 0);
		builder1->addVertex();
		builder1->setAttrib3v<Float>(material1->a_position, +0.25, +0.25, -1.5f);
		builder1->setAttrib3v<Float>(material1->a_normal, 0, 0, 1);
		builder1->setAttrib3v<Float>(material1->a_color, 1, 1, 1);
		builder1->setAttrib2v<Float>(material1->a_tex0uv, 1, 0);
		builder1->addVertex();
		builder1->setAttrib3v<Float>(material1->a_position, +0.25, -0.25, -1.5f);
		builder1->setAttrib3v<Float>(material1->a_normal, 0, 0, 1);
		builder1->setAttrib3v<Float>(material1->a_color, 1, 1, 1);
		builder1->setAttrib2v<Float>(material1->a_tex0uv, 1, 1);
		builder1->addVertex();
		builder1->setAttrib3v<Float>(material1->a_position, -0.25, -0.25, -1.5f);
		builder1->setAttrib3v<Float>(material1->a_normal, 0, 0, 1);
		builder1->setAttrib3v<Float>(material1->a_color, 1, 1, 1);
		builder1->setAttrib2v<Float>(material1->a_tex0uv, 0, 1);
		builder1->addIndices(0, 1, 2);
		builder1->addIndices(0, 2, 3);
		
		model = modelb->build();
		//scene->addChild(model);
		//scene->addChild(im);
		
		/* Others things */
		
		tr = new CKThread(&func);
		tr->init(nullptr);
		
		test();
		
		image = new CKImage((Char*)"test.png");
		image2 = new CKImage((Char*)"download2.png");
		image3 = new CKImage((Char*)"test2.png");
		
		tex = new CKTexture(image);
		tex2 = new CKTexture(image2);
		tex3 = new CKTexture(image3);
		
		model->tex0 = tex;
		
		window->getSize(&ww, &wh);
		fb = new CKFrameBuffer();
		
		cam = new CKPov3D(0.05f, 1000.0f, 60.0f*(CKMath::PI/180.0f), 800.0f/480.0f);
		mat = CKMat3();
		mat.identity();
		this->scene3d->view = cam;
		
		renderer->copr.enableDepthTest();
		renderer->copr.enableStencilTest();
		renderer->copr.enableOpacity();
		renderer->copr.enableFaceCulling();
		
		if(!fb->setup(CK_FRAMEBUFFERMODE_COLOR, ww, wh)){
			std::cout << "Error on FrameBuffer setup!" << std::endl;
		}
		
	}
	
	void e_update(){
		glClearColor(1, 1, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		{
			CKVec3 mov = CKVec3(0, 0, 0);
			
			if(inputh->isKeyPressed('w')&&(inputh->getModKeys()&CKI_MOD_LCTRL)){
				std::cout << "Enter!" << std::endl;
			}
			if(inputh->isKeyPressed('a')){
				mov.x += .01;
			}
			if(inputh->isKeyPressed('d')){
				mov.x -= .01;
			}
			if(inputh->isKeyPressed('s')){
				mov.z -= .01;
			}
			if(inputh->isKeyPressed('w')){
				mov.z += .01;
			}
			if(inputh->isKeyPressed('f')){
				mov.y += .01;
			}
			if(inputh->isKeyPressed('r')){
				mov.y -= .01;
			}
			if(inputh->isKeyPressed('p')){
				speaker->reset(musica);
			}
			if(inputh->isKeyPressed(SDLK_LEFT)){
				cam->rotation.y -= .01;
			}
			if(inputh->isKeyPressed(SDLK_RIGHT)){
				cam->rotation.y += .01;
			}
			if(inputh->isKeyPressed(SDLK_UP)){
				cam->rotation.x -= .01;
			}
			if(inputh->isKeyPressed(SDLK_DOWN)){
				cam->rotation.x += .01;
			}
			if(inputh->isKeyPressed(SDLK_o)){
				model->rotation.x += 0.005f;
			}
			if(inputh->isKeyPressed(SDLK_l)){
				model->rotation.x -= 0.005f;
			}
			
			
			CKMat4 rot = CKMat4();
			rot.setToRotationX(cam->rotation.x);
			rot.rotateY(cam->rotation.y);
			mov.transformPoint(&rot);
			
			cam->position.add(&mov);
		}
		
	}
	
	void e_end(){
		
		delete model;
		delete modelb;
		
		delete scene3d;
		
		delete tr;
		
		delete cam;
		
		delete fb;
		
		delete tex2;
		delete tex;
		
		delete image2;
		delete image;
		
		delete musica;
		delete musica2;
		delete speaker;
	}
	
public:
	TestCore(CKCoreApplicationSettings *sets):CKCore(sets){
		
	}
	
};



#endif // test_h
