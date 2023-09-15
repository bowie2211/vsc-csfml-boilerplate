/* Main file as a template for a project using the CSFML library

Used:
CSFML-2.5.1-windows-32-bit
ISO C11 Standard

A rectangle is moved across the screen at a constant speed.
The current coordinates are displayed as text.
The program can be exited using the Esc key.

*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Window/Export.h>
#include <SFML/Window/Keyboard.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void waitdt_ms(double tt_ms); // Function waits for tt_ms and then returns

int main()
{
    sfVideoMode mode;         // Structure for specifying screen resolution and color depth
    sfRenderWindow* window;   // This pointer variable is used to access the graphics output area in the program
    sfEvent sf_event;         // Events such as mouse clicks and keyboard inputs are stored here
    sfRectangleShape* rec;    // Pointer to a rectangle object that can be accessed
    sfVector2f rec_pos, rec_size, text_pos; // sfVector is a structure with x and y fields, used for specifying coordinates or lengths and widths
    sfFont* font = sfFont_createFromFile("arial.ttf"); // This pointer allows you to set the font for a text element
    // Pointer variable to access the text object
    sfText* text_obj_x_pos; // This sfText object is used for displaying the x-position
    sfText* text_obj_y_pos; // This sfText object is used for displaying the y-position
    sfText* explain_text_obj_x_pos; // Explanation text for x-position display
    sfText* explain_text_obj_y_pos; // Explanation text for y-position display

    char txt_buffer[15]; // String variable where the conversion result of the numerical x-value is temporarily stored
    // Wait time in ms before the program continues. This can be used to control the speed at which the rectangle moves across the screen
    int waiting_time = 100;

    // Create output window and set properties
    mode.height = 900; // Height in pixels
    mode.width = 900;  // Width in pixels
    mode.bitsPerPixel = 32;
    // Create an output window object, which could also be done directly in the definition section above
    window = sfRenderWindow_create(mode, "My Window", sfResize | sfClose, NULL);

    // Create graphical elements and set properties
    // Create a rectangle
    // Position
    rec_pos.x = 500;
    rec_pos.y = 500;
    // Size
    rec_size.x = 100;
    rec_size.y = 100;
    // Create a rectangle object and assign it to the previously defined pointer variable
    rec = sfRectangleShape_create();
    // Set the properties of the rectangle
    sfRectangleShape_setFillColor(rec, sfWhite); // CSFML defines various colors like sfWhite, sfBlack, etc., which can be found in Color.h
    sfRectangleShape_setPosition(rec, rec_pos);
    sfRectangleShape_setSize(rec, rec_size);

    // Create text elements and set properties:
    // Example: Get and display the position
    text_pos.x = 0;
    text_pos.y = 0;

    explain_text_obj_x_pos = sfText_create(); // Create a text object
    sfText_setFont(explain_text_obj_x_pos, font);
    sfText_setPosition(explain_text_obj_x_pos, text_pos);
    sfText_setString(explain_text_obj_x_pos, "x_pos:");

    text_pos.x += 100; // Move the x-position to the right
    text_obj_x_pos = sfText_create(); // Create a text object
    sfText_setFont(text_obj_x_pos, font);
    sfText_setPosition(text_obj_x_pos, text_pos);

    // Reset the variables for text position
    text_pos.x = 0;
    text_pos.y = 0;
    text_pos.y += 30; // New position for the next text (move down)
    
    explain_text_obj_y_pos = sfText_create(); // Create a text object
    sfText_setFont(explain_text_obj_y_pos, font);
    sfText_setPosition(explain_text_obj_y_pos, text_pos);
    sfText_setString(explain_text_obj_y_pos, "y_pos:");

    text_pos.x += 100; // Move the x-position to the right
    text_obj_y_pos = sfText_create(); // Create a text object
    sfText_setFont(text_obj_y_pos, font);
    sfText_setPosition(text_obj_y_pos, text_pos);

    // Infinite loop as long as the graphics window is open
    while (sfRenderWindow_isOpen(window)) {

        // Clear the screen
        sfRenderWindow_clear(window, sfBlack); // Clear the output window (erase the old "frame")

        // Calculate: Area for processing the algorithmic part

        if (rec_pos.x > 700) {
            rec_pos.x = 500;
            rec_pos.y = 500;
        }

        rec_pos.x++;
        rec_pos.y++;

        // Change: Modify the properties of the elements

        sfRectangleShape_setPosition(rec, rec_pos); // Set new coordinates for the rectangle

        itoa(sfRectangleShape_getPosition(rec).x, txt_buffer, 10); // Convert the numerical x-position value to a string
        sfText_setString(text_obj_x_pos, txt_buffer);
        itoa(sfRectangleShape_getPosition(rec).y, txt_buffer, 10); // Convert the numerical y-position value to a string
        sfText_setString(text_obj_y_pos, txt_buffer);

        // Draw: Draw the rectangle with current properties on the output window
        sfRenderWindow_drawRectangleShape(window, rec, NULL); // NOTE: This is not displayed yet; you need to call display below
        sfRenderWindow_drawText(window, explain_text_obj_x_pos, NULL);
        sfRenderWindow_drawText(window, text_obj_x_pos, NULL);
        sfRenderWindow_drawText(window, explain_text_obj_y_pos, NULL);
        sfRenderWindow_drawText(window, text_obj_y_pos, NULL);

        // Wait: Wait for waiting_time ms before the program continues
        waitdt_ms(waiting_time);

        // Display: Show the current state of the graphical elements on the output window
        sfRenderWindow_display(window);

        // Event loop is required to check if, for example, the window was closed or a key was pressed
        while (sfRenderWindow_pollEvent(window, &sf_event)) {
            if (sf_event.type == sfEvtClosed)
                sfRenderWindow_close(window);

            if (sf_event.type == sfEvtKeyPressed) { // Check if a keyboard input occurred
                // Check if the ESC key was pressed and if so, exit the program
                if (sf_event.key.code == sfKeyEscape) // The codes for different keys can be found in Keyboard.h
                    sfRenderWindow_close(window);
            }
        }
    }
}

void waitdt_ms(double tt_ms)
{
    /*waitdt_ms
    -----------
    Waits for tt_ms milliseconds
    */
    clock_t time1;
    clock_t dt_ms = 0;
	time1 = clock();  /*REQUEST PROCESSOR TIME, OR LOCAL TIME, NO PROBLEM WHICH.*/
	while (dt_ms < tt_ms) { /* WAIT: holds the program execution here until tt_sec passers. */
		dt_ms = (clock() - time1) / (CLOCKS_PER_SEC / 1000.0);
	}
}