#ifndef LAYER_H
#define LAYER_H

typedef struct {
	float value; // greyscale 0.0 to 1.0
} Cell;

typedef enum {
	BLEND_REPLACE, // default
	BLEND_ADD,
	BLEND_MULTIPLY,
	BLEND_MAX
} BlendMode;

typedef struct {
	void (*process)(void *self, Cell *buffer, int w, int h, float aspect);
	void (*update)(void *self, float dt);
	void *data;
	BlendMode blend;
	const char *name;
} Layer;

#endif
