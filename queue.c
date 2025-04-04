#include "queue.h"
#include "tile_game.h"

void print_tiles(struct game_state state1, struct game_state state2)
{
    //printf("Checking state!\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //printf("tile[%d][%d]: %2d, %2d ", i, j, state1.tiles[i][j], state2.tiles[i][j]);
            //printf("tile[%d][%d]: %2d ", i, j, state1.tiles[i][j]);
        }
        //printf("\n");
    }
}

void print_queue_tiles(struct queue *q)
{
    struct list_node *current = q->data.head;
    printf("\n----------Queue contents----------\n");
    while (current != NULL)
    {
        struct game_state game = deserialize(current->value);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                //printf("tile[%d][%d]: %2d, %2d ", i, j, state1.tiles[i][j], state2.tiles[i][j]);
                printf("tile[%d][%d]: %2d ", i, j, game.tiles[i][j]);
            }
            printf("\n");
        }
        printf("\n");
     current = current->next;
    }
}

// Function to print the linked list in the queue
void print_linked_list(struct linked_list *list) {
    struct list_node *current = list->head;
    printf("\nLinked list: \n");
    
    while (current != NULL) {
        printf("%zu -> ", current->value);
        current = current->next;
    }
    
    printf("NULL\n\n");
}

void print_queue(struct queue *q) {
    struct list_node *current = q->data.head;
    //printf("\nQueue contents:\nQueue: ");
    while (current != NULL) {
        //printf("%zu -> ", current->value); // Assuming value is of type size_t
        current = current->next;
    }
    //printf("NULL\n\n");
}

int same_state(struct game_state state1, struct game_state state2)
{
    //print_tiles(state1, state2);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (state1.tiles[i][j] != state2.tiles[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}

/*int is_visited(struct linked_list *visited_states, size_t serialized_state)
{
    struct list_node *current = visited_states->head;
    struct game_state state2 = deserialize(serialized_state);

    while (current != NULL)
    {
        struct game_state state1 = deserialize(current->value);
        

        if (same_state(state1, state2))
        {
            return 1;
        }
        current = current->next;
    }

    return 0;
}*/
int is_visited(struct linked_list *visited_states, struct game_state state2)
{
    struct list_node *current = visited_states->head;

    while (current != NULL)
    {
        struct game_state state1 = deserialize(current->value); // Deserialize current node value
        //print_tiles(state1, state2);
        if (same_state(state1, state2)) // Check if states are the same
        {
            return 1; // State is visited
        }
        current = current->next; // Move to the next node in the list
    }

    return 0; // State not found in the visited list
}


void enqueue(struct queue *q, struct game_state state) 
{
    size_t serialized_state = serialize(state);
    //printf("Adding serialized state to queue: %zu\n", serialized_state);
    insert_at_tail(&q->data, serialized_state);
}

struct game_state dequeue(struct queue *q) 
{ 
    if (q->data.head == NULL)
    {
        return (struct game_state){0}; 
    }
    
    size_t serialized_state = remove_from_head(&q->data);

    return deserialize(serialized_state);
}

/*int number_of_moves(struct game_state start) 
{
    struct queue q; // Game queue
    q.data.head = NULL; // init queue

    enqueue(&q, start); // enqueue init state
    print_queue(&q);
    // Init a list of states that have been visited
    struct linked_list visited_states; // States that have been visited
    visited_states.head = NULL;

    size_t serialized_initial = serialize(start); // Serialize the starting grid
    insert_at_tail(&visited_states, serialized_initial); // insert it into the queue

    // The goal state to reach
    struct game_state goal_state = 
    {
        .tiles = 
        {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 0}
        },

        .empty_row = 3,
        .empty_col = 3,
        .num_steps = 0
    };

    printf("The correct serial: %zu\n", serialize(goal_state));

    int while_count = 0;
    while (q.data.head != NULL && (while_count < 10))
    {
        print_queue(&q);
        print_linked_list(&visited_states);
        struct game_state current_state = dequeue(&q);
        
        printf("Number of moves right now: %d\n", current_state.num_steps);

        struct list_node *check_node = q.data.head;

        while (check_node != NULL)
        {
            struct game_state queued_state = deserialize(check_node->value);
            if (same_state(queued_state, goal_state)) 
            {
                printf("Goal state found in queue!\n");
                free_list(q.data);
                free_list(visited_states);
                return while_count;
            }
            check_node = check_node->next;
        }

        if (same_state(current_state, goal_state))
        {
            free_list(q.data);
            return while_count;
        }

        else
        {
            for (int i = 0; i < 4; i++)
            {
                struct game_state next_state = copy_state(current_state); // The current state with one more move

                if (i == 0) move_up(&next_state);
                if (i == 1) move_down(&next_state);
                if (i == 2) move_left(&next_state);
                if (i == 3) move_right(&next_state);


                size_t serialized_next = serialize(next_state); // The serialized version of the next state

                if (!is_visited(&visited_states, serialized_next))
                {
                    
                    enqueue(&q, next_state);
                    insert_at_tail(&visited_states, serialized_next);
                }
                else
                {
                    printf("State visisted: skipping\n");
                }
            }
        }
        while_count++;
    }
    
    free_list(q.data);
    free_list(visited_states);
    return 0; 
}*/

int number_of_moves(struct game_state start) 
{
    struct queue q;
    q.data.head = NULL; 

    enqueue(&q, start); 
    //print_queue(&q);

    
    struct linked_list visited_states;
    visited_states.head = NULL;

    size_t serialized_initial = serialize(start);
    insert_at_tail(&visited_states, serialized_initial);

    // Goal state
    struct game_state goal_state = 
    {
        .tiles = 
        {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 0}
        },
        .empty_row = 3,
        .empty_col = 3,
        .num_steps = 0
    };

    //printf("Goal state serialized: %zu\n", serialize(goal_state));
    if (same_state(start, goal_state))
    {
        return 0;
    }

    // BFS Loop
    //int while_count = 0;
    int size_linked_list = 0;
    while (q.data.head != NULL) 
    {
        //printf("Ran %d times\n", size_linked_list);
        struct game_state current_state = dequeue(&q);
        
        for (int i = 0; i < 4; i++)
        {
            struct game_state next_state = current_state;

            // Move operations
            if (i == 0) move_down(&next_state);
            if (i == 1) move_up(&next_state);
            if (i == 2) move_right(&next_state);
            if (i == 3) move_left(&next_state);

            next_state.num_steps = current_state.num_steps + 1;

            if (same_state(next_state, goal_state)) 
            {
                //printf("Took %d steps\n", next_state.num_steps);
                free_list(q.data);
                free_list(visited_states);
                return next_state.num_steps;
            }

            size_t serialized_next = serialize(next_state);

            if (!is_visited(&visited_states, next_state))
            {
                ++size_linked_list;
                insert_at_tail(&visited_states, serialized_next); 
                enqueue(&q, next_state); 
                if (size_linked_list > 1000)
                {
                    remove_from_head(&visited_states);
                }
            }
        }
    }

        //print_linked_list(&visited_states);
        //print_queue(&q);
        //print_queue_tiles(&q);
        

    free_list(q.data);
    free_list(visited_states);
    return -1; 

}



