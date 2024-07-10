#include "node.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 768
#define NODE_RADIUS 15
#define NODE_PADDING 30
#define TEXT_PADDING 10
#define FONT_PATH "OS.ttf"

template <typename T>
class TreeGUI
{
private:
    Node<T> *root;
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    int screen_width;
    int screen_height;
    int node_radius;
    int node_padding;
    int text_padding;
    int text_size;
    int tree_height;

    int calculate_tree_height(Node<T> *node, int level)
    {
        if (node == nullptr)
        {
            return level;
        }
        int max_height = level;
        for (auto child : node->get_children())
        {
            int child_height = calculate_tree_height(child, level + 1);
            if (child_height > max_height)
            {
                max_height = child_height;
            }
        }
        return max_height;
    }

    void draw_node(Node<T> *node, size_t level, int left_bound, int right_bound)
    {
        if (node == nullptr)
        {
            return;
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        int x = (left_bound + right_bound) / 2;
        int y = level * (node_padding) + node_radius * 3;

        // Draw the circle outline of the node
        int circle_x = x - node_radius;
        int circle_y = y - node_radius;
        int circle_diameter = 2 * node_radius;

        for (int i = 0; i < circle_diameter; i++)
        {
            for (int j = 0; j < circle_diameter; j++)
            {
                int dx = i - node_radius;
                int dy = j - node_radius;
                if (dx * dx + dy * dy <= node_radius * node_radius)
                {
                    SDL_RenderDrawPoint(renderer, circle_x + i, circle_y + j);
                }
            }
        }

        // Draw the text
        std::stringstream ss;
        ss << node->get_value();
        ss.clear();
        SDL_Surface *surface = TTF_RenderText_Solid(font, ss.str().c_str(), {0, 0, 0, 255});
        if (surface == nullptr)
        {
            std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
            return;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (texture == nullptr)
        {
            std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
            return;
        }

        int textPos_x = x - node_radius;
        int textPos_y = y - node_radius * 2;
        SDL_Rect text_rect = {textPos_x, textPos_y, 2 * text_size, text_size};
        SDL_RenderCopy(renderer, texture, NULL, &text_rect);

        if (node->get_children().size() > 0)
        {
            int new_bound = (right_bound - left_bound) / node->get_children().size();

            for (size_t i = 0; i < node->get_children().size(); i++)
            {
                int child_x1 = left_bound + i * new_bound;
                int child_x2 = left_bound + (i + 1) * new_bound;
                SDL_RenderDrawLine(renderer, x, y, (child_x1 + child_x2) / 2, y + node_radius + node_padding);
                draw_node(node->get_children()[i], level + 1, child_x1, child_x2);
            }
        }

        SDL_DestroyTexture(texture);
    }

public:
    TreeGUI(Node<T> *root) : root(root), window(nullptr), renderer(nullptr), font(nullptr)
    {
        tree_height = calculate_tree_height(root, 0);
        screen_width = SCREEN_WIDTH;
        screen_height = SCREEN_HEIGHT;
        node_radius = 100 / (tree_height + 1);
        node_padding = screen_height / (tree_height + 1);
        text_padding = TEXT_PADDING;
        text_size = node_radius;

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            throw std::invalid_argument("SDL_Init failed");
        }
        if (TTF_Init() != 0)
        {
            std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
            SDL_Quit();
            throw std::invalid_argument("TTF_Init failed");
        }
        window = SDL_CreateWindow("Tree", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
        if (window == nullptr)
        {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            TTF_Quit();
            SDL_Quit();
            throw std::invalid_argument("Window creation failed");
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr)
        {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            TTF_Quit();
            SDL_Quit();
            throw std::invalid_argument("Renderer creation failed");
        }
        font = TTF_OpenFont(FONT_PATH, text_size);
        if (font == nullptr)
        {
            std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            TTF_Quit();
            SDL_Quit();
            throw std::invalid_argument("Font loading failed");
        }
    }

    void draw()
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        draw_node(root, 0, 0, screen_width);

        SDL_RenderPresent(renderer);

        // Loop to keep the window open
        bool close = false;
        SDL_Event event;
        while (!close)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    close = true;
                }
            }
        }

        // clear the screen
        SDL_RenderClear(renderer);
        // clean the resources and close the window
        closeGUI();
    }

    void closeGUI()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
    }
};
