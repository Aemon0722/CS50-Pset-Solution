#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
bool marked[MAX];
bool inStack[MAX];
void merge_sort(pair array[], int start_index, int end_index);
void merge_sort_array(pair array[], int start_index, int middle, int end_index);
bool dfs(int i);

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            vote(j, name, ranks);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // search through the all the candidate name
    for (int i = 0; i < candidate_count; i++)
    {
        // to check if current candidate name match the name of the vote
        if (strcmp(candidates[i], name) == 0)
        {
            // represents the user's ith preference
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Start the loop to record preference from the candidate who have the highest preference
    for (int i = 0; i < candidate_count; i++)
    {
        // start the loop to record candidates who have lower preference
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

void merge_sort(pair array[], int start_index, int end_index)
{
    // if there is only one size left, the start index will greater or equal to end_index
    // for instance the last portion of array is 9, then start index could equal to 10 or 9 depend the left or right side
    if(start_index >= end_index )
    {
        return;
    }
    else
    {
        // find the middle index
        int middle = start_index + (end_index - start_index) / 2;
        //sort left hand side
        merge_sort(array, start_index, middle);
        //sort right hand side
        merge_sort(array, middle + 1, end_index);
        merge_sort_array(array, start_index, middle, end_index);
    }
}

void merge_sort_array(pair array[], int start_index, int middle, int end_index)
{
    // size for the temporary array
    int left = middle - start_index +1;
    int right = end_index - middle;

    // temporary array to store sorted values
    pair temp_left [left];
    pair temp_right [right];

    for(int i = 0; i < left; i++)
    {
        temp_left[i] = array[start_index + i];
    }

    for(int i = 0; i < right; i++)
    {
        temp_right[i] = array[middle + 1 + i];
    }

    // loop from the start index to the end index of the array, so need to include the end_index for the size of the array
    for(int l = 0, r = 0, k = start_index; k <= end_index; k++)
    {
        if(l < left && r >= right)
        {
            array[k] = temp_left[l];
            l++;
        }
        else if(r < right && l >= left)
        {
            array[k] = temp_right[r];
            r++;
        }
        else if(r < right && l < left)
        {
            int str1 = preferences[temp_left[l].winner][temp_left[l].loser] - preferences[temp_left[l].loser][temp_left[l].winner];
            int str2 = preferences[temp_right[r].winner][temp_right[r].loser] - preferences[temp_right[r].loser][temp_right[r].winner];
            if(str1 >= str2)
            {
                array[k] = temp_left[l];
                l++;
            }
            else
            {
                array[k] = temp_right[r];
                r++;
            }
        }
    }
}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    merge_sort(pairs, 0, pair_count - 1);

}

// Depth First Search to detect circle
bool dfs(int a)
{
    // Base case; if node has been visited and explored, end search by return true
    if (marked[a] == true && inStack[a] == true)
    {
        return true;
    }
    // marked the node as visited
    marked[a] = true;
    // trace the node whether it is in the current path
    inStack[a] = true;
    for (int j = 0; j < candidate_count; j++)
    {
        // find whether there is neighbor of the node(the loser side)
        if (locked[a][j] == true)
        {
            // check if the next node has already been explored, if yes then there is a circle
            if (dfs(j) == true)
            {
                return true;
            }
        }
        // continue to find next neighbor until no neighbor left
    }
    // unmark the trace for exploring another node
    inStack[a] = false;
    // end the recursive call for as that node has been completed explored
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0, count = 0; i < pair_count; i++)
    {
        // locked the first pair of winner and loser
        locked[pairs[i].winner][pairs[i].loser] = true;
        for (int j = 0; j < candidate_count; j++)
        {
            // clear the graph from previous tracing before another tracing from the start node
            marked[j] = false;
        }
        // skip that pair if locking this pair create circle
        if (dfs(pairs[i].winner) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
}

void find(int i)
{
    bool check = false;
    for (int j = 0; j < candidate_count; j++)
    {
        // check if there is no one beating that candidate
        if (locked[j][i] == true)
        {
            check = true;
        }
    }
    if (check == false)
    {
        printf("%s\n", candidates[i]);
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        find(i);
    }
}
