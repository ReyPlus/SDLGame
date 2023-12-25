# Documentation
This is a guide to using SDLGame. SDLGame is built with an object oriented focus. It has classes with basic functionality that can be used as parents in inheritance.

## Startup
Below is boiler plate code. This can be put into main.cpp to create a game window with the name "Boiler Plate". The logic() and draw() method will run every frame. logic() is a space for computations and conditions. All of the game logic to occur and keep together. draw() is to contain the rendering functionality. Game inherits from Base_Game. More details on Base_Game below.

```c++
class Game : public Base_Game {
public:
    Game(const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, Uint32 windowFlags) : Base_Game(name, x, y, width, height, windowFlags) {
        
    }
private:
    void logic() {}

    void draw() {}

private:
};

int main() {
    Game::INIT(SDL_INIT_EVERYTHING, IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP, MIX_INIT_MP3);
    Game* game = new Game("Boiler Plate", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);

    game->loop();

    return 0;
}
```

## Base_Game.h
### mouse (Mouse)
- Has int x and int y that update each time mouse movement is detected.
- leftHeld and rightHeld are bools that will return whether the associated button is being held down or not.
- leftPressed() and rightPressed() return bools. Will only return true if the mouse was clicked in that frame, otherwise will be false.
- getPos(int& x, int& y) can be used to retrieve the current position. A simpler method is just to use the x and y data members stored in mouse to grab the most recent position.

### kbd (Keyboard)
- checkPressed(SDL_Scancode key) returns bool of if the key was pressed or not that frame.
- checkHeld(SDL_Scancode key) returns bool if the key is being held down.

### gfx (Graphics)
- putPixel(...) will render a pixel to the screen.
- putLine(...) will render a line to the screen.
- putRect(...) will render a rectangle to the screen.
- putCircle(...) will render a circle to the screen.

## Font.h
### Font
- Used to store a loaded Font.
- Font(...) constructor takes in multiple params. The first is the path to the .ttf file. The second is the font size to use when rendering text from it. The third is the color for the font to render text as.
- getColor() returns the color of the font.
- getTTF() gets the TTF_Font SDL pointer.

### Text
- Text uses the message to render, the font to render it from, and the renderer.
- setText is used to render a new message.
- modify(callable) takes in a callable that is used to modify the current text, then renders the new text.
- move() and moveCentered() move where the text is rendered. move() moves the text by the top left corner, while moveCentered() moved it by the center.
- draw() is used to render the texture to the window.

## Image.h
### Image
- Image(...) takes in the file path of the image, it's position and size, the renderer, degrees to rotate, and a flip flag. Creates the texture from the data provided.
- move() moves the location of where to render the image (by top left)
- setSize() sets how big the image should be when rendered.
- draw() renders the texture to the window.

## Sound.h
### Effect (for sound effects)
- Effect(path) takes in the file path of the sound effect to use.
- play() plays the sound.

### Music (for playable stored music)
- The Music class is a static class, so only one Music file can be loaded at a time.
- load(path) loads the music file at the file path
- play() plays the music.
- pause() pauses the music.
- end() stops the music.

## Base_GUI.h
- Has Base classes to inherit from that have basic functionality.
- Base_Clickable can detect if it's hovered/clicked and has a click() method to handle what should happen when clicked. Buttons are an example use.
- Base_Switch inherits from Base_Clickable. It makes the click() method act as a toggle with an on/off state. Checkboxes and toggles are example uses.
- Base_Bar is for progress bars. Uses doubles to track the percentage. More for purely display.
- Base_Slider inherits from Base_Bar and is an interface due to having isDragged(int x, int y) and isClicked(int x, int y) as pure virtual methods. Meant to be an interactable progress bar.
