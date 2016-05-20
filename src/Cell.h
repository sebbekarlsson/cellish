#include <GL/freeglut.h>
#include <string>

extern const int CELL_SIZE;
using namespace std;

class Cell: public Instance {
    public:
        string character;
        bool selected;
        float writeTimer;
        float text_r, text_g, text_b;
        float border_r, border_g, border_b;
        float write_r, write_g, write_b;

        Cell (float x, float y, string character) : Instance(x, y) {
            this->w = CELL_SIZE;
            this->h = CELL_SIZE;
            this->character = character;

            this->text_r = 255.0f;
            this->text_g = 255.0f;
            this->text_b = 255.0f;

            this->border_r = 40.0f;
            this->border_g = 40.0f;
            this->border_b = 40.0f;

            this->write_r = rand() % 255 + 0;;
            this->write_g = rand() % 255 + 0;;
            this->write_b = rand() % 255 + 0;;

            this->writeTimer = 0.0f;
        }

        void draw(float delta) {
            this->text_r = 255.0f;
            this->text_g = 255.0f;
            this->text_b = 255.0f;

            glDisable(GL_TEXTURE_2D);
            glColor3f(border_r/255.0f, border_g/255.0f, border_b/255.0f);

            glPushMatrix();

            if (this->writeTimer > 0) {
                glColor3f(write_r/255.0f, write_g/255.0f, write_b/255.0f);
                glPushMatrix();
                glTranslatef(this->x, this->y, 0.0f);

                glBegin(GL_QUADS);

                glVertex2f(0.0f, 0.0f);
                glVertex2f(0.0f, this->h);
                glVertex2f(this->w, this->h);
                glVertex2f(this->w, 0.0f);
                glVertex2f(0.0f, this->h);
                
                glEnd();
                glPopMatrix();

                text_r = (255.0 - write_r);
                text_g = (255.0 - write_g);
                text_b = (255.0 - write_b);
            }

            glTranslatef(this->x, this->y, -0.1f);

            glBegin(GL_LINES);

            glVertex2f(0.0f, this->h);
            glVertex2f(this->w, this->h);
            
            glEnd();
            
            glPopMatrix();

            glPushMatrix();
            glColor3f(text_r/255.0f, text_g/255.0f, text_b/255.0f);
            glTranslatef(this->x+CELL_SIZE/4, this->y+CELL_SIZE-4, 0.0f);
            glScalef(CELL_SIZE/186.0f, -(CELL_SIZE/186.0f), CELL_SIZE/186.0f);

            for (auto c = this->character.begin(); c != this->character.end(); ++c)
            {
                glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *c);
            }

            glPopMatrix();

            glEnable(GL_TEXTURE_2D);
        }

        void tick(float delta) {
            if (this->selected == true) {
                this->border_r = 255.0f;
                this->border_g = 255.0f;
                this->border_b = 255.0f;
            } else {
                this->border_r = 40.0f;
                this->border_g = 40.0f;
                this->border_b = 40.0f; 
            }
            if (this->writeTimer > 0) {
                this->writeTimer -= 1.0f;
            }
            this->selected = false;
        }
};
