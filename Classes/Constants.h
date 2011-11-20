//
//  Copyright (C) Ricardo Ruiz López, 2010. All rights reserved.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

// pieces
#define NUMBER_OF_PIECES_PER_GIRL 5

// girls
#define NUMBER_OF_GIRLS 1
#define NUMBER_OF_FRAMES_PER_GIRL 11

// user interface logic
#define TRANSITION_DURATION 1
#define BACKGROUND_MENU_ROTATION_TIME 24
#define BACKGROUND_ROTATION_TIME 12

// game logic
#define REGENERATIONS_PER_GIRL 2
#define MATCHES_PER_REGENERATION 4
#define POINTS_ADDED_WHEN_NORMAL_MATCH 2
#define POINTS_ADDED_WHEN_WILDCARD_MATCH 4
#define POINTS_REMOVED_WHEN_INCORRECT_MATCH 0

#define MEDIUM_MODE_STARTS_IN_LEVEL 10
#define HARD_MODE_STARTS_IN_LEVEL 50

#define TIMEBAR_DURATION_IN_EASY_MODE 30		// 60
#define TIMEBAR_DURATION_IN_MEDIUM_MODE 45
#define TIMEBAR_DURATION_IN_HARD_MODE 30 

#define EXTRA_PAIRS_IN_EASY_MODE 2
#define EXTRA_PAIRS_IN_MEDIUM_MODE 1
#define EXTRA_PAIRS_IN_HARD_MODE 0

#define TIME_GIVEN_IN_EASY_MODE 4
#define TIME_GIVEN_IN_MEDIUM_MODE 3
#define TIME_GIVEN_IN_HARD_MODE 2

#define TIME_REMOVED_IN_EASY_MODE 4
#define TIME_REMOVED_IN_MEDIUM_MODE 5
#define TIME_REMOVED_IN_HARD_MODE 6


// board
#define NUMBER_OF_COLUMNS_IN_BOARD 7
#define NUMBER_OF_ROWS_IN_BOARD 7
#define BORDER_MARGIN_IN_PIXELS 3 // used to calculate pieces positions in board properly
#define REGENERATION_BOARD_DURATION 1
#define CHANGE_GIRL_DURATION 1

// Used by BoardPiecePlace and Board where these resources are loaded.
#define PIECE_SPRITE_TAG 666
#define SELECTION_SPRITE_TAG 777
#define MATCHING_SPRITE_TAG 111

// score sizes used by HighscoreCell and Local/GlobalHighscoresViewController
#define RANK_WIDTH_PERCENTAGE 0.08
#define NAME_WIDTH_PERCENTAGE (1.0-RANK_WIDTH_PERCENTAGE-COUNTRY_WIDTH_PERCENTAGE-SCORE_WIDTH_PERCENTAGE-LEVEL_WIDTH_PERCENTAGE)
#define COUNTRY_WIDTH_PERCENTAGE 0.26
#define SCORE_WIDTH_PERCENTAGE 0.2
#define LEVEL_WIDTH_PERCENTAGE 0.12

// server
#define SERVER_TIMEOUT 14