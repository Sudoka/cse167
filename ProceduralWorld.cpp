#include <string.h>
#include <cstdlib>
#include <string>
#include <math.h>
#include "GlutWindow.h"
#include "SGMatrixTransform.h"
#include "SGSphere.h"
#include "SGCuboid.h"
#include "SGCylinder.h"
#include "Material.h"
#include "SGRobot.h"
#include "SGCity.h"
#include "SGGrid.h"
#include "SGSphere.h"
#include "SGLSystem.h"
#include "DrawSegmentAction.h"
#include "DrawSegmentMaterialAction.h"
#include "SGLight.h"
#include "SGTexturedPlane.h"

using namespace std;

Material getRandomBaseMaterial();
SGNode *getSceneGraph();
static const double TILE_SIZE = 1.0;
static const double TILE_HEIGHT = 0.05;
static const double ROBOT_HEIGHT = 1.0;

static Vector4 sGAmbient(0.0, 0.2, 0.0, 1.0);
static Vector4 sGDiffuse(0.0, 0.8, 0.0, 1.0);
static Vector4 sGSpecular(1.0, 1.0, 1.0, 1.0);
static double shininess = 50.0;
static Material shinyGreen(sGAmbient, sGDiffuse, sGSpecular, shininess);

static Vector4 dBAmbient(0.2, 0.06, 0.02, 1.0);
static Vector4 dBDiffuse(0.4, 0.15, 0.05, 1.0);
static Vector4 dBSpecular(0.0, 0.0, 0.0, 1.0);
static Material diffuseBrown(dBAmbient, dBDiffuse, dBSpecular, shininess);

static Vector4 silverAmbient(0.1, 0.1, 0.1, 1.0);
static Vector4 silverDiffuse(0.8, 0.8, 0.8, 1.0);
static Vector4 silverSpecular(0.0, 0.0, 0.0, 1.0);
static Material silver(silverAmbient, silverDiffuse, silverSpecular, shininess);

static Vector4 sRAmbient(0.1, 0.0, 0.0, 1.0);
static Vector4 sRDiffuse(1.0, 0.0, 0.0, 1.0);
static Vector4 sRSpecular(1.0, 1.0, 1.0, 1.0);
static Material shinyRed(sRAmbient, sRDiffuse, sRSpecular, shininess);

SGNode *getWavyTree() {
    multimap<char, LSystemRule*> *rules = new multimap<char, LSystemRule*>();
    map<char, TurtleAction*> *variableActions = new map<char, TurtleAction*>();
    string base("F");
    string ruleF1("F[-F[&F+F+F]]");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF1, 0.93)));
    string ruleF2("^/&AF");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF2, 0.03)));
    string ruleF3("^/GF");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF3, 0.04)));
    
    string ruleA("A");
    rules->insert(pair<char, LSystemRule*>('A', new LSystemRule(ruleA, 1.0)));
    
    string ruleG("G");
    rules->insert(pair<char, LSystemRule*>('G', new LSystemRule(ruleG, 1.0)));
    
    (*variableActions)['F'] = new DrawSegmentAction(0.4);
    (*variableActions)['G'] = new DrawSegmentAction(0.4);
    (*variableActions)['A'] = new DrawSegmentAction(0.4);
    
    return new SGLSystem(silver, base, rules, variableActions, 25, 3);
}

SGNode *getSpikyTree() {
    multimap<char, LSystemRule*> *rules = new multimap<char, LSystemRule*>();
    map<char, TurtleAction*> *variableActions = new map<char, TurtleAction*>();
    string base("F");
    string ruleF1("F[//^F[&F+/F-F]]");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF1, 0.93)));
    string ruleF2("^/&AF");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF2, 0.03)));
    string ruleF3("^/GF");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF3, 0.04)));
    
    string ruleA("A");
    rules->insert(pair<char, LSystemRule*>('A', new LSystemRule(ruleA, 1.0)));
    
    string ruleG("G");
    rules->insert(pair<char, LSystemRule*>('G', new LSystemRule(ruleG, 1.0)));
    
    (*variableActions)['F'] = new DrawSegmentAction(0.4);
    (*variableActions)['G'] = new DrawSegmentAction(0.4);
    (*variableActions)['A'] = new DrawSegmentAction(0.4);
    
    return new SGLSystem(getRandomBaseMaterial(), base, rules, variableActions, 25, 3);
}

SGNode *getStraightTree() {
    multimap<char, LSystemRule*> *rules = new multimap<char, LSystemRule*>();
    map<char, TurtleAction*> *variableActions = new map<char, TurtleAction*>();
    string base("F");
    string ruleF1("FF[[+^//F][-\\\\F]]");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF1, 0.93)));
    string ruleF2("^/&AF");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF2, 0.03)));
    string ruleF3("^/GF");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF3, 0.04)));
    
    string ruleA("A");
    rules->insert(pair<char, LSystemRule*>('A', new LSystemRule(ruleA, 1.0)));
    
    string ruleG("G");
    rules->insert(pair<char, LSystemRule*>('G', new LSystemRule(ruleG, 1.0)));
    
    (*variableActions)['F'] = new DrawSegmentAction(0.4);
    (*variableActions)['G'] = new DrawSegmentAction(0.4);
    (*variableActions)['A'] = new DrawSegmentAction(0.4);
    
    return new SGLSystem(getRandomBaseMaterial(), base, rules, variableActions, 25, 3);
}

SGNode *getWeed() {
    multimap<char, LSystemRule*> *rules = new multimap<char, LSystemRule*>();
    map<char, TurtleAction*> *variableActions = new map<char, TurtleAction*>();
    string base("F");
    string ruleF1("F[&+F]F[->F][->F][&F]");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF1, 0.93)));
    string ruleF2("^/AF");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF2, 0.03)));
    string ruleF3("^//GF");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF3, 0.04)));
    
    string ruleA("A");
    rules->insert(pair<char, LSystemRule*>('A', new LSystemRule(ruleA, 1.0)));
    
    string ruleG("G");
    rules->insert(pair<char, LSystemRule*>('G', new LSystemRule(ruleG, 1.0)));
    
    (*variableActions)['F'] = new DrawSegmentAction(0.4);
    (*variableActions)['G'] = new DrawSegmentAction(0.4);
    (*variableActions)['A'] = new DrawSegmentAction(0.4);
    
    return new SGLSystem(getRandomBaseMaterial(), base, rules, variableActions, 25, 3);
}

SGNode *getTwistyTree() {
    multimap<char, LSystemRule*> *rules = new multimap<char, LSystemRule*>();
    map<char, TurtleAction*> *variableActions = new map<char, TurtleAction*>();
    string base("F");
    string ruleF1("FF-^/[-F+F+F]+[+F-F-F]");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF1, 0.93)));
    string ruleF2("^/AF");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF2, 0.03)));
    string ruleF3("^//GF");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF3, 0.04)));
    
    string ruleA("A");
    rules->insert(pair<char, LSystemRule*>('A', new LSystemRule(ruleA, 1.0)));
    
    string ruleG("G");
    rules->insert(pair<char, LSystemRule*>('G', new LSystemRule(ruleG, 1.0)));
    
    (*variableActions)['F'] = new DrawSegmentAction(0.4);
    (*variableActions)['G'] = new DrawSegmentAction(0.4);
    (*variableActions)['A'] = new DrawSegmentAction(0.4);
    
    return new SGLSystem(getRandomBaseMaterial(), base, rules, variableActions, 25, 3);
}

SGNode *getRegularLeafyTree() {
    multimap<char, LSystemRule*> *rules = new multimap<char, LSystemRule*>();
    map<char, TurtleAction*> *variableActions = new map<char, TurtleAction*>();
    
//    Angle : 25
//# Iterations: 6
//Branch radius: 0.02
//Branch radius reduction: 0.0015
//Branch length (height): 0.15
//Initial value : fffffA
//Production rules : A = f[++Al][--Al]>>>A
    
    string base("FFFFFA");
    string ruleA("F[++AL][--AL]>>>A");
    rules->insert(pair<char, LSystemRule*>('A', new LSystemRule(ruleA, 1.0)));
    string ruleF2("F");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF2, 1.0)));
    
    string ruleG("L");
    rules->insert(pair<char, LSystemRule*>('L', new LSystemRule(ruleG, 1.0)));
    
    (*variableActions)['F'] = new DrawSegmentAction(0.4);
    (*variableActions)['L'] = new DrawSegmentMaterialAction(shinyGreen, 0.2);
    (*variableActions)['A'] = new DrawSegmentMaterialAction(shinyGreen, 0.2);
    
    return new SGLSystem(getRandomBaseMaterial(), base, rules, variableActions, 25, 5);
}

SGNode *getSpikyLeafyTree() {
    multimap<char, LSystemRule*> *rules = new multimap<char, LSystemRule*>();
    map<char, TurtleAction*> *variableActions = new map<char, TurtleAction*>();
    
//Angle : 30
//# Iterations: 10
//Branch radius: 0.01
//Branch radius reduction: 0.001
//Branch length (height): 0.16
//Initial value : fA
//Production rules : A = f[^Bl]>>[^Bl]>>A, B = f[-Bl]B
    
    string base("FA");
    string ruleA("F[^BL]>>[^BL]>>A");
    rules->insert(pair<char, LSystemRule*>('A', new LSystemRule(ruleA, 1.0)));
    string ruleB("F[-BL]B");
    rules->insert(pair<char, LSystemRule*>('B', new LSystemRule(ruleB, 1.0)));
    
    string ruleF("F");
    rules->insert(pair<char, LSystemRule*>('F', new LSystemRule(ruleF, 1.0)));
    string ruleG("L");
    rules->insert(pair<char, LSystemRule*>('L', new LSystemRule(ruleG, 1.0)));
    
    (*variableActions)['F'] = new DrawSegmentAction(0.4);
    (*variableActions)['L'] = new DrawSegmentMaterialAction(shinyGreen, 0.1);
    (*variableActions)['A'] = new DrawSegmentAction(0.2);
    (*variableActions)['B'] = new DrawSegmentAction(0.1);
    
    return new SGLSystem(getRandomBaseMaterial(), base, rules, variableActions, 40, 6);
}

SGNode *getLight() {
    Matrix4 lightTransformMatrix;
    lightTransformMatrix.toTranslationMatrix(0.0, 50.0, 0.0);
    
    //    GLfloat pointlight_ambient[] = {0.3, 0.3, 0.3, 1.0};
//    GLfloat pointlight_diffuse[] = {1.0, 1.0, 1.0, 1.0};
//    GLfloat pointlight_specular[] = {0.3, 0.3, 0.3, 1.0};
//    GLfloat pointlight_position[] = { 0.0, 90.0, 5.0, 1.0 };
    
    Vector4 ambient(0.5, 0.5, 0.5, 1.0);
    Vector4 diffuse(1.0, 1.0, 1.0, 1.0);
    Vector4 specular(0.3, 0.3, 0.3, 1.0);
    Vector3 dir(0.0, -1.0, 0.0);
    
    SGMatrixTransform *lightTransform 
            = new SGMatrixTransform(lightTransformMatrix);
    lightTransform->addChild(new SGLight(1, ambient, diffuse, specular, dir, 1800.0));
    return lightTransform;
//    SGLight(int lightIndex, Vector4 ambient, Vector4 diffuse, 
//        Vector4 specular, Vector3 spotDir, double spotCutoff);
}

static const int GRID_ROWS = 10;
static const int GRID_COLS = 10;
static const double GRID_X_SIZE = 100.0;
static const double GRID_Z_SIZE = 100.0;
static const int NUM_GENERATORS = 6;
static const int TREES_TO_PLACE = 20;
static const int MIN_TREE_INDEX = 2;
static const int MAX_TREE_INDEX = 7;
typedef SGNode *(*GeneratorFunction)(void);
static GeneratorFunction generatorFunctions[NUM_GENERATORS];

int randomRange(int min, int max) {
    int range = max - min + 1;
    return min + rand() % range;
}

int randomParkCol() {
    while (true) {
        int random = randomRange (0, GRID_COLS - 1);
        
        if (random != 2 && random != 7) return random;
    }
}

int randomParkRow() {
    return randomRange(0, GRID_ROWS - 1);
}

// 0.2 chance of a returning silver
Material getRandomBaseMaterial() {
  int random = randomRange(1, 5);

  if (random == 1) {
    return silver;
  } else {
    return diffuseBrown;
  }
}

void setGeneratorFunctions() {
    generatorFunctions[0] = &getWavyTree;
    generatorFunctions[1] = &getSpikyTree;
    generatorFunctions[2] = &getStraightTree;

    generatorFunctions[3] = &getRegularLeafyTree;
    generatorFunctions[4] = &getSpikyLeafyTree;
    generatorFunctions[5] = &getTwistyTree;
    //    generatorFunctions[6] = &getWeed;
}

GeneratorFunction getRandomGeneratorFunction() {
  return generatorFunctions[randomRange(0, NUM_GENERATORS - 1)];
}

SGNode *getParkGrid() {
    SGGrid *grid = new SGGrid(GRID_ROWS, GRID_COLS, GRID_X_SIZE, GRID_Z_SIZE);
    
    //grid->addChild(generatorFunctions[6](), 4, 4);

    for (int i = 0; i < TREES_TO_PLACE; i++) {
        int randomRow = randomParkRow();
        int randomCol = randomParkCol();
	
	while (grid->isOccupied(randomRow, randomCol)) {
	    randomRow = randomParkRow();
	    randomCol = randomParkCol();
	}

	grid->addChild((getRandomGeneratorFunction())(), randomRow, randomCol);
    }
    /*    
    for (int i = 0 ; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            if (!grid->isOccupied(i, j)) {
                grid->addChild(new SGSphere(shinyRed, 1.0), i, j);
            }
        }
    }
    */
    return grid;
}

SGNode *getSceneGraph() {
    Vector4 ambient(0.0, 0.0, 0.2, 1.0);
    Vector4 diffuse(0.0, 0.0, 1.0, 1.0);
    Vector4 specular(1.0, 1.0, 1.0, 1.0);
    double shininess = 50.0;
    Material shinyBlue(ambient, diffuse, specular, shininess); 
    
    ambient.set(0.1, 0.1, 0.1, 1.0);
    diffuse.set(1.0, 1.0, 1.0, 1.0);
    specular.set(1.0, 1.0, 1.0, 1.0);
    Material shinyWhite(ambient, diffuse, specular, shininess);
    
    ambient.set(0.1, 0.1, 0.1, 1.0);
    diffuse.set(0.0, 0.8, 0.0, 1.0);
    specular.set(0.0, 0.0, 0.0, 1.0);
    Material diffuseGreen(ambient, diffuse, specular, shininess);
    
    ambient.set(0.1, 0.0, 0.0, 1.0);
    diffuse.set(1.0, 0.0, 0.0, 1.0);
    specular.set(1.0, 1.0, 1.0, 1.0);
    Material shinyRed(ambient, diffuse, specular, shininess);
    
    SGMatrixTransform *world = new SGMatrixTransform();

    world->addChild(getLight());

    world->addChild(getParkGrid());
    world->addChild(new SGCity(shinyWhite, 100, 100));
    

    return world;
}

// SDMB Hash from General Hash functions library
unsigned int SDBMHash(char* str, unsigned int len)
{
  unsigned int hash = 0;
  unsigned int i    = 0;

  for(i = 0; i < len; str++, i++)
    {
      hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }

  return hash;
}

int main(int argc, char** argv) {
/*    Vector3 cam(0.0, 5.0, 5.0);
    Vector3 lookAt(0.0, 0.0, 0.0);
    Vector3 up(0.0, 1.0, 0.0);*/

    int seed = time(NULL); // if no argument, random seed
    if (argc > 1)
      seed = SDBMHash(argv[1], strlen(argv[1])); 

    srand(seed);
    
     setGeneratorFunctions();
    
    Vector3 cam(0.0, 1.0, 10.0);
    Vector3 lookAt(0.0, 1.0, -15.0);
    Vector3 up(0.0, 1.0, 0.0); 

    string name("Procedural World");
    
    GlutWindow::initializeWindow(512, 512, &argc, argv, name);

    GlutWindow::setSceneGraphFunction(getSceneGraph);
    GlutWindow::setCamera(cam, lookAt, up);
    GlutWindow::enterGlutMainLoop();

    return 0;
}

























