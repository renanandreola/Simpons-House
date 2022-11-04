#include "Scene6.h"

CScene6::CScene6()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;
	
	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	// Cria gerenciador de impress�o de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 100.0f, 100.0f, 3.0f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	// Carrega todas as texturas
	pTextures = new CTexture();	
	pTextures->CreateTextureClamp(0, "../Scene1/back.bmp");
	pTextures->CreateTextureClamp(1, "../Scene1/front.bmp");
	pTextures->CreateTextureClamp(2, "../Scene1/down.bmp");
	pTextures->CreateTextureClamp(3, "../Scene1/up.bmp");
	pTextures->CreateTextureClamp(4, "../Scene1/left.bmp");
	pTextures->CreateTextureClamp(5, "../Scene1/right.bmp");

	pTextures->CreateTextureLinear(6, "../Scene1/water.bmp");

	pTextures->CreateTextureTGA(7, "../Scene6/arvore.tga");
	pTextures->CreateTextureTGA(8, "../Scene6/cerca.tga");
	pTextures->CreateTextureTGA(9, "../Scene6/jan.tga");

	// Carrega o objeto
	//pCena1 = NULL;
	//pCena1 = new CModel_3DS();
	//pCena1->Load("../Scene6/Cena1.3DS");

	pCasa = NULL;
	pCasa = new CModel_3DS();
	pCasa->Load("../Scene6/Casa1.3DS");
}


CScene6::~CScene6(void)
{
	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
	}

	if (pTextures)
	{
		delete pTextures;
		pTextures = NULL;
	}

	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}

	if (pTimer)
	{
		delete pTimer;
		pTimer = NULL;
	}	



	if (pCena1)
	{
		delete pCena1;
		pCena1 = NULL;
	}

	if (pCasa)
	{
		delete pCasa;
		pCasa = NULL;
	}
}




int CScene6::DrawGLScene(void)	// Fun��o que desenha a cena
{
	// Get FPS
	if (GetTickCount() - ulLastFPS >= 1000)	// When A Second Has Passed...
	{
		ulLastFPS = GetTickCount();				// Update Our Time Variable
		iFPS = iFrames;							// Save The FPS
		iFrames = 0;							// Reset The FPS Counter
	}
	iFrames++;									// FPS counter
	
	pTimer->Update();							// Atualiza o timer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual


	// Seta as posi��es da c�mera
	pCamera->setView();

	// Desenha grid 
	//Draw3DSGrid(20.0f, 20.0f);

	// Desenha os eixos do sistema cartesiano
	DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espa�o)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (IN�CIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);

	// SkyBox
	/*CreateSkyBox(0.0f, 200.0f, 0.0f,
		3000.0f, 3000.0f, 3000.0f,
		pTextures);*/

	// Cena1
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	//pCena1->Draw();
	pCasa->Draw();
	glPopMatrix();


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	pTextures->ApplyTexture(7);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -60.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, 200.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, 200.0f, 0.0f);
		glEnd();
	glPopMatrix();

	
	pTextures->ApplyTexture(7);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -60.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f,   0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 50.0f,   0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 50.0f, 200.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, 200.0f, 0.0f);
		glEnd();
	glPopMatrix();	

	pTextures->ApplyTexture(8);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 40.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-40.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(40.0f, 15.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-40.0f, 15.0f, 0.0f);
		glEnd();
	glPopMatrix();

	pTextures->ApplyTexture(8);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -40.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-40.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(40.0f, 15.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-40.0f, 15.0f, 0.0f);
	glEnd();
	glPopMatrix();

	/*pTextures->ApplyTexture(8);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -40.0f);
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-40.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(40.0f, 15.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-40.0f, 15.0f, 0.0f);
	glEnd();
	glPopMatrix();*/

	pTextures->ApplyTexture(9);
	glPushMatrix();
		glTranslatef(0.0f, 30.0f, 0.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-40.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(40.0f, 15.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-40.0f, 15.0f, 0.0f);
			glEnd();
	glPopMatrix();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);

	//
	


	

	//// Habilita Blending
	//glEnable(GL_BLEND);
	//// Configura fun��o de Blending
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glColor4f(1.0f, 1.0f, 1.0f, 0.7f);

	//glPushAttrib(GL_TEXTURE_BIT);
	//// Unidade de Textura 0
	//glActiveTexture(GL_TEXTURE0);
	//glEnable(GL_TEXTURE_2D);
	//pTextures->ApplyTexture(6);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	//glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_REPLACE);


	//// Unidade de Textura 1
	//glActiveTexture(GL_TEXTURE1);
	//glEnable(GL_TEXTURE_2D);
	//pTextures->ApplyTexture(6);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	//glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);

	//glPushMatrix();
	//glTranslatef(0.0f, 60.0f, 0.0f);
	//glBegin(GL_QUADS);
	//glNormal3f(0.0f, 0.0f, 1.0f);
	//glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f + fRenderPosY);
	//glMultiTexCoord2f(GL_TEXTURE1, 0.0f + fRenderPosY, 0.0f);
	//glVertex3f(-550.0f, 0.0f, -250.0f);

	//glMultiTexCoord2f(GL_TEXTURE0, 5.0f, 0.0f + fRenderPosY);
	//glMultiTexCoord2f(GL_TEXTURE1, 5.0f + fRenderPosY, 0.0f);
	//glVertex3f(-550.0f, 0.0f, 250.0f);

	//glMultiTexCoord2f(GL_TEXTURE0, 5.0f, 5.0f + fRenderPosY);
	//glMultiTexCoord2f(GL_TEXTURE1, 5.0f + fRenderPosY, 5.0f);
	//glVertex3f(550.0f, 0.0f, 250.0f);

	//glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 5.0f + fRenderPosY);
	//glMultiTexCoord2f(GL_TEXTURE1, 0.0f + fRenderPosY, 5.0f);
	//glVertex3f(550.0f, 0.0f, -250.0f);
	//glEnd();
	//glPopMatrix();

	//glActiveTexture(GL_TEXTURE1);
	//glDisable(GL_TEXTURE_2D);
	//glActiveTexture(GL_TEXTURE0);
	//glDisable(GL_TEXTURE_2D);
	//glPopAttrib();

	//// Desabilita Blending
	//glDisable(GL_BLEND);


	
	glDisable(GL_TEXTURE_2D);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.002f;

	// Impress�o de texto na tela...
	// Muda para modo de proje��o ortogonal 2D
	// OBS: Desabilite Texturas e Ilumina��o antes de entrar nesse modo de proje��o
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 100, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

	// Cor da fonte
	glColor3f(1.0f, 1.0f, 0.0f);


	glRasterPos2f(10.0f, 0.0f);	// Posicionando o texto na tela
	if (!bIsWireframe) {
		pTexto->glPrint("[TAB]  Modo LINE"); // Imprime texto na tela
	}
	else {
		pTexto->glPrint("[TAB]  Modo FILL");
	}


	//// Camera LookAt
	glRasterPos2f(10.0f, 40.0f);
	pTexto->glPrint("Player LookAt  : %f, %f, %f", pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);

	//// Posi��o do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplica��o e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime()/1000));


	glPopMatrix();

	// Muda para modo de proje��o perspectiva 3D
	PerspectiveMode();

	return true;
}




void CScene6::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os c�lculos de rota��o da vis�o do Player (atrav�s das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a c�mera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene6::KeyPressed(void) // Tratamento de teclas pressionadas
{

	// Verifica se a tecla 'W' foi pressionada e move o Player para frente
	if (GetKeyState('W') & 0x80)
	{
		pCamera->moveGlob(pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);
	}
	// Verifica se a tecla 'S' foi pressionada e move o Player para tras
	else if (GetKeyState('S') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Forward[0], -pCamera->Forward[1], -pCamera->Forward[2]);
	}
	// Verifica se a tecla 'A' foi pressionada e move o Player para esquerda
	else if (GetKeyState('A') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Right[0], -pCamera->Right[1], -pCamera->Right[2]);
	}
	// Verifica se a tecla 'D' foi pressionada e move o Player para direira
	else if (GetKeyState('D') & 0x80)
	{
		pCamera->moveGlob(pCamera->Right[0], pCamera->Right[1], pCamera->Right[2]);
	}
	// Sen�o, interrompe movimento do Player
	else
	{
	}



}

void CScene6::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
		pTimer->Init();
		break;

	case VK_RETURN:
		break;

	}

}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene6::Draw3DSGrid(float width, float length)
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.3f, 0.0f);
	glPushMatrix();
	for (float i = -width; i <= length; i += 1)
	{
		for (float j = -width; j <= length; j += 1)
		{
			// inicia o desenho das linhas
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0.0f, j + 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 1, 0.0f, j + 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 1, 0.0f, j);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0.0f, j);
			glEnd();
		}
	}
	glPopMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void CScene6::DrawCube(float pX, float pY, float pZ,
	float rX, float rY, float rZ, float angle,
	float sX, float sY, float sZ,
	int texID)
{

	// Seta a textura ativa
	if (texID >= 0)
		pTextures->ApplyTexture(texID);

	glPushMatrix();
	glTranslatef(pX, pY, pZ);
	glRotatef(angle, rX, rY, rZ);
	glScalef(sX, sY, sZ);

	glBegin(GL_QUADS);
	// face frente
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f, 0.5f);

	// face tr�s
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	
	// face direita
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);

	// face esquerda
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	// face baixo
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f( 0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f( 0.5f, -0.5f,  0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  0.5f);

	// face cima
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f,  0.5f,  0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f,  0.5f,  -0.5f);

	glEnd();

	glPopMatrix();
}


void CScene6::DrawAxis()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);

	// Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
	glPopMatrix();
}


void CScene6::CreateSkyBox(float x, float y, float z,
	float width, float height, float length,
	CTexture* pTextures)
{
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPushMatrix();

	// Centraliza o Skybox em torno da posi��o especificada(x, y, z)
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;


	// Aplica a textura que representa a parte da frente do skybox (BACK map)
	pTextures->ApplyTexture(0);

	// Desenha face BACK do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (FRONT map)
	pTextures->ApplyTexture(1);

	// Desenha face FRONT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (DOWN map)
	pTextures->ApplyTexture(2);

	// Desenha face BOTTOM do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (UP map)
	pTextures->ApplyTexture(3);

	// Desenha face TOP do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (LEFT map)
	pTextures->ApplyTexture(4);

	// Desenha face LEFT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glEnd();


	// Aplica a textura que representa a parte da frente do skybox (RIGHT map)
	pTextures->ApplyTexture(5);

	// Desenha face RIGHT do cubo do skybox
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	glPopMatrix();
}