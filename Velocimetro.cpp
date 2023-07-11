#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <sstream>

float speed = 0.0f; // Velocidade atual em km/h

void drawText(const std::string& text, float x, float y, void* font = GLUT_BITMAP_HELVETICA_18) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(font, c);
    }
}

void saveScreenshot(const std::string& filename, int width, int height) {
    unsigned char* pixels = new unsigned char[3 * width * height];
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    FILE* file = fopen(filename.c_str(), "wb");
    if (file) {
        unsigned char pngFileHeader[14] = {
            'B', 'M', // Tipo do arquivo
            0, 0, 0, 0, // Tamanho do arquivo (preenchido posteriormente)
            0, 0, // Reservado
            0, 0, // Reservado
            54, 0, 0, 0 // Offset do início dos dados da imagem
        };

        unsigned char pngInfoHeader[40] = {
            40, 0, 0, 0, // Tamanho do header do png
            0, 0, 0, 0, // Largura da imagem (preenchido posteriormente)
            0, 0, 0, 0, // Altura da imagem (preenchido posteriormente)
            1, 0, // Número de planos de cor
            24, 0, // Bits por pixel
            0, 0, 0, 0, // Tipo de compressão (sem compressão)
            0, 0, 0, 0, // Tamanho dos dados da imagem (preenchido posteriormente)
            0, 0, 0, 0, // Resolução horizontal em pixels por metro
            0, 0, 0, 0, // Resolução vertical em pixels por metro
            0, 0, 0, 0, // Número de cores na paleta
            0, 0, 0, 0 // Número de cores importantes
        };

        int dataSize = width * height * 3;
        int fileSize = 54 + dataSize;

        pngFileHeader[2] = (unsigned char)(fileSize);
        pngFileHeader[3] = (unsigned char)(fileSize >> 8);
        pngFileHeader[4] = (unsigned char)(fileSize >> 16);
        pngFileHeader[5] = (unsigned char)(fileSize >> 24);

        pngInfoHeader[4] = (unsigned char)(width);
        pngInfoHeader[5] = (unsigned char)(width >> 8);
        pngInfoHeader[6] = (unsigned char)(width >> 16);
        pngInfoHeader[7] = (unsigned char)(width >> 24);
        pngInfoHeader[8] = (unsigned char)(height);
        pngInfoHeader[9] = (unsigned char)(height >> 8);
        pngInfoHeader[10] = (unsigned char)(height >> 16);
        pngInfoHeader[11] = (unsigned char)(height >> 24);

        fwrite(pngFileHeader, 1, 14, file);
        fwrite(pngInfoHeader, 1, 40, file);
        fwrite(pixels, 1, dataSize, file);
        fclose(file);
    }

    delete[] pixels;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Desenhar o velocímetro
    float cx = 200.0f;
    float cy = 200.0f;
    float radiusOuter = 150.0f;
    float radiusInner = 120.0f;
    int numTicks = 10;

    // Desenhar o aro externo
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        float x = cx + radiusOuter * cos(angle);
        float y = cy + radiusOuter * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    // Desenhar o aro interno
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0f;
        float x = cx + radiusInner * cos(angle);
        float y = cy + radiusInner * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    // Desenhar os marcadores de velocidade
    float tickLengthOuter = 15.0f;
    float tickLengthInner = 10.0f;
    float tickAngle = (360.0f / numTicks) * M_PI / 180.0f;
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    for (int i = 0; i < numTicks; i++) {
        float angle = i * tickAngle;
        float cosAngle = cos(angle);
        float sinAngle = sin(angle);

        // Marcadores externos
        float x1 = cx + (radiusOuter - tickLengthOuter) * cosAngle;
        float y1 = cy + (radiusOuter - tickLengthOuter) * sinAngle;
        float x2 = cx + radiusOuter * cosAngle;
        float y2 = cy + radiusOuter * sinAngle;
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();

        // Marcadores internos
        x1 = cx + (radiusInner - tickLengthInner) * cosAngle;
        y1 = cy + (radiusInner - tickLengthInner) * sinAngle;
        x2 = cx + radiusInner * cosAngle;
        y2 = cy + radiusInner * sinAngle;
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }

    // Desenhar o ponteiro de velocidade
    float angle = ((speed / 200.0f) * 180.0f - 90.0f) * M_PI / 180.0f;
    float pointerLength = radiusInner - 10.0f;
    float px = cx + pointerLength * cos(angle);
    float py = cy + pointerLength * sin(angle);
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(px, py);
    glEnd();

    // Desenhar o texto da velocidade
    std::stringstream ss;
    ss << "Velocidade: " << speed << " km/h";
    drawText(ss.str(), cx - 80.0f, cy - radiusOuter - 40.0f);

    glutSwapBuffers();
}

void update(int value) {
    // Atualizar a velocidade
    speed += 1.0f;
    if (speed > 200.0f) {
        speed = 0.0f;
    }

    std::stringstream ss;
    ss << "screenshot_" << speed << ".png";
    saveScreenshot(ss.str(), 400, 400);

    glutPostRedisplay();
    glutTimerFunc(100, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Velocímetro");
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
