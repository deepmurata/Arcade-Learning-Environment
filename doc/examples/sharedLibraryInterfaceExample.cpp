/* *****************************************************************************
 * A.L.E (Arcade Learning Environment)
 * Copyright (c) 2009-2013 by Yavar Naddaf, Joel Veness, Marc G. Bellemare,
 *  Matthew Hausknecht, and the Reinforcement Learning and Artificial Intelligence 
 *  Laboratory
 * Released under the GNU General Public License; see License.txt for details. 
 *
 * Based on: Stella  --  "An Atari 2600 VCS Emulator"
 * Copyright (c) 1995-2007 by Bradford W. Mott and the Stella team
 *
 * *****************************************************************************
 *  ale_interface.hpp
 *
 *  The shared library interface.
 **************************************************************************** */

#include <iostream>
#include <ale_interface.hpp>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " rom_file" << std::endl;
        return 1;
    }

    ALEInterface ale;

    // Get & Set the desired settings
    int max_frames_per_episode = ale.getInt("max_num_frames_per_episode");
    ale.set("random_seed", 123);

    // Load the ROM file. (Also resets the system for new settings to
    // take effect.)
    ale.loadROM(argv[1]);

    // Get the vector of legal actions
    ActionVect legal_actions = ale.getLegalActionSet();

    // Play 10 episodes
    for (int episode=0; episode<10; episode++) {
        float totalReward = 0;
        while (!ale.game_over()) {
            Action a = legal_actions[rand() % legal_actions.size()];
            // Apply the action and get the resulting reward
            float reward = ale.act(a);
            totalReward += reward;
        }
        cout << "Episode " << episode << " ended with score: " << totalReward << endl;
        ale.reset_game();
    }
};
