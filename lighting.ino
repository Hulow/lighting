#include <FastLED.h>

#define NUM_LEDS_PER_CONE 60
#define BRIGHTNESS 150
#define LED_TYPE WS2815
#define COLOR_ORDER GRB

// Define a CRGB array for each strip
CRGB cone1[NUM_LEDS_PER_CONE];
CRGB cone2[NUM_LEDS_PER_CONE];
CRGB cone3[NUM_LEDS_PER_CONE];
CRGB cone4[NUM_LEDS_PER_CONE];
CRGB cone5[NUM_LEDS_PER_CONE];
CRGB cone6[NUM_LEDS_PER_CONE];
CRGB cone7[NUM_LEDS_PER_CONE];
CRGB cone8[NUM_LEDS_PER_CONE];
CRGB cone9[NUM_LEDS_PER_CONE];
CRGB cone10[NUM_LEDS_PER_CONE];
CRGB cone11[NUM_LEDS_PER_CONE];
CRGB cone12[NUM_LEDS_PER_CONE];
CRGB cone13[NUM_LEDS_PER_CONE];
CRGB cone14[NUM_LEDS_PER_CONE];
CRGB cone15[NUM_LEDS_PER_CONE];
CRGB cone16[NUM_LEDS_PER_CONE];

CRGB* allCones[] = {
  cone1, cone2, cone3, cone4,
  cone5, cone6, cone7, cone8,
  cone9, cone10, cone11, cone12,
  cone13, cone14, cone15, cone16
};

CRGB* group1[] = { cone1, cone2 };
CRGB* group2[] = { cone3, cone4 };
CRGB* group3[] = { cone5, cone6 };
CRGB* group4[] = { cone7, cone8 };
CRGB* group5[] = { cone9, cone10 };
CRGB* group6[] = { cone11, cone12 };
CRGB* group7[] = { cone13, cone14 };
CRGB* group8[] = { cone15, cone16 };

CRGB** allGroups[] = {
  group1, group2, group3, group4,
  group5, group6, group7, group8
};

const CRGB RED_COLOR = CRGB(200, 0, 0); 
const int NUM_CONES = sizeof(allCones) / sizeof(allCones[0]);
const int NUM_GROUPS = sizeof(allGroups) / sizeof(allGroups[0]);
const int CONES_PER_GROUP = 2;
int previousIndex = -1;
int previousScenario = -1;

void setup() {
  FastLED.setBrightness(BRIGHTNESS);

  FastLED.addLeds<LED_TYPE, 2, COLOR_ORDER>(cone1, NUM_LEDS_PER_CONE);
  FastLED.addLeds<LED_TYPE, 3, COLOR_ORDER>(cone2, NUM_LEDS_PER_CONE);
  FastLED.addLeds<LED_TYPE, 4, COLOR_ORDER>(cone3, NUM_LEDS_PER_CONE);
  FastLED.addLeds<LED_TYPE, 5, COLOR_ORDER>(cone4, NUM_LEDS_PER_CONE);
  FastLED.addLeds<LED_TYPE, 6, COLOR_ORDER>(cone5, NUM_LEDS_PER_CONE);
  FastLED.addLeds<LED_TYPE, 7, COLOR_ORDER>(cone6, NUM_LEDS_PER_CONE);
  FastLED.addLeds<LED_TYPE, 8, COLOR_ORDER>(cone7, NUM_LEDS_PER_CONE);
  FastLED.addLeds<LED_TYPE, 9, COLOR_ORDER>(cone8, NUM_LEDS_PER_CONE);
  FastLED.addLeds<LED_TYPE, 10, COLOR_ORDER>(cone9, NUM_LEDS_PER_CONE);
  FastLED.addLeds<LED_TYPE, 11, COLOR_ORDER>(cone10, NUM_LEDS_PER_CONE);
  FastLED.addLeds<LED_TYPE, 12, COLOR_ORDER>(cone11, NUM_LEDS_PER_CONE);
  FastLED.addLeds<LED_TYPE, 13, COLOR_ORDER>(cone12, NUM_LEDS_PER_CONE);
  FastLED.addLeds<LED_TYPE, 22, COLOR_ORDER>(cone13, NUM_LEDS_PER_CONE);
  FastLED.addLeds<LED_TYPE, 23, COLOR_ORDER>(cone14, NUM_LEDS_PER_CONE);
  FastLED.addLeds<LED_TYPE, 24, COLOR_ORDER>(cone15, NUM_LEDS_PER_CONE);
  FastLED.addLeds<LED_TYPE, 25, COLOR_ORDER>(cone16, NUM_LEDS_PER_CONE);

  FastLED.clear(); 
  FastLED.show();
}

int getRandomScenario(int totalScenarios) {
  int newScenario;
  do {
    newScenario = random(totalScenarios);
  } while (newScenario == previousScenario);
  previousScenario = newScenario;
  return newScenario;
}

int getRandomGroupIndex(int totalGroups) {
  int newIndex;  // <-- Declare newIndex here
  do {
    newIndex = random(totalGroups);
  } while (newIndex == previousIndex);
  previousIndex = newIndex;
  return newIndex;
}

CRGB* mergedGroup[CONES_PER_GROUP * 2];
void prepareMergedGroup(CRGB** dest, CRGB** groupA, CRGB** groupB) {
  for (int i = 0; i < CONES_PER_GROUP; i++) {
    dest[i] = groupA[i];
    dest[i + CONES_PER_GROUP] = groupB[i];
  }
}

void increaseBrightness(CRGB* cones[], int numCones, int numLeds, const CRGB& color) {
  for (uint8_t brightness = 0; brightness <= BRIGHTNESS; brightness++) {
    for (int cone = 0; cone < numCones; cone++) {
      for (int led = 0; led < numLeds; led++) {
        cones[cone][led] = color;
      }
      nscale8(cones[cone], numLeds, brightness);
    }
    FastLED.show();
    delay(1);
  }
}

void decreaseBrightness(CRGB* cones[], int numCones, int numLeds) {
  for (int brightness = BRIGHTNESS; brightness >= 0; brightness -= 10) {
    for (int i = 0; i < numCones; i++) {
      nscale8(cones[i], numLeds, brightness);  // scale down brightness
    }
    FastLED.show();
    delay(50);
  }
}

void lightUpLEDsAcrossGroup(CRGB* group[], int numCones, int numLeds, const CRGB& color, int delayMs = 1) {
  for (int ledIndex = 0; ledIndex < numLeds; ledIndex++) {
    for (uint8_t brightness = 0; brightness <= BRIGHTNESS; brightness+=50) {
      for (int cone = 0; cone < numCones; cone++) {
        group[cone][ledIndex] = color;
        group[cone][ledIndex].nscale8_video(brightness);
      }
      FastLED.show();
      delay(delayMs);
    }
  }
}

void blinkCones(CRGB* cones[], int numCones, int numLeds, const CRGB& color, int blinkDelay = 100) {
  for (int cone = 0; cone < numCones; cone++) {
    fill_solid(cones[cone], numLeds, color);
  }
  FastLED.show();
  delay(blinkDelay);

  for (int cone = 0; cone < numCones; cone++) {
    fill_solid(cones[cone], numLeds, CRGB::Black);
  }
  FastLED.show();
  delay(blinkDelay);
}

void loop() {
  int scenario = getRandomScenario(5); 

  CRGB** activeCones = nullptr;
  int activeConeCount = 0;

  if (scenario == 0) {
    int idx1 = getRandomGroupIndex(NUM_GROUPS);
    int idx2 = getRandomGroupIndex(NUM_GROUPS);
    prepareMergedGroup(mergedGroup, allGroups[idx1], allGroups[idx2]);
    activeCones = mergedGroup;
    activeConeCount = CONES_PER_GROUP * 2;

  } else if (scenario == 1) {
    int idx = getRandomGroupIndex(NUM_GROUPS);
    activeCones = allGroups[idx];
    activeConeCount = CONES_PER_GROUP;

  } else if (scenario == 2 ) {
    static CRGB* selectedCones[4];
    int usedIndices[NUM_CONES] = {0};
    int count = 0;

    while (count < 4) {
      int randIndex = random(NUM_CONES);
      if (usedIndices[randIndex] == 0) {
        usedIndices[randIndex] = 1;
        selectedCones[count] = allCones[randIndex];
        count++;
      }
    }
    activeCones = selectedCones;
    activeConeCount = 4;
  } else if (scenario == 3) {
    static CRGB* selectedCones[4];
    int usedIndices[NUM_CONES] = {0};
    int count = 0;

    while (count < 4) {
      int randIndex = random(NUM_CONES);
      if (usedIndices[randIndex] == 0) {
        usedIndices[randIndex] = 1;
        selectedCones[count] = allCones[randIndex];
        count++;
      }
    }
    activeCones = selectedCones;
    activeConeCount = 4;
    blinkCones(activeCones, activeConeCount, NUM_LEDS_PER_CONE, RED_COLOR);

  } else { 
    activeCones = allCones;
    activeConeCount = NUM_CONES;
  }

  lightUpLEDsAcrossGroup(activeCones, activeConeCount, NUM_LEDS_PER_CONE, RED_COLOR);

  if (random(0, 4) == 1) {
    blinkCones(activeCones, activeConeCount, NUM_LEDS_PER_CONE, RED_COLOR);
  }

  decreaseBrightness(activeCones, activeConeCount, NUM_LEDS_PER_CONE);
}

