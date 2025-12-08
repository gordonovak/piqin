#pragma once
#include <vector>
#include "engine/particles/ParticleGroup.hpp"
#include "../utilities/SparseVector.hpp"

namespace geng {
    // Manages all the particles in the scene
    class ParticleManager {
    private:
        gutils::SparseVector<geng::ParticleGroup> groups;
        std::vector<int> groups_removed;

    public:
        // Construct/destruct
        ParticleManager();
        ~ParticleManager();

        // Updates all particle groups
        void update();

        ParticleGroup *find_by_object(const Actor *o);

        // Adds a particle to the group
        ParticleGroup*& add(ParticleGroup* g);

        void add(std::vector<ParticleGroup *> &groups);

        // Lets a particle die out by ending
        static void dissolve(ParticleGroup* g);
        void dissolve(const Actor *o); //Removes particle groups for actors

        // Removes a particle from the sparse vector
        void remove(ParticleGroup* g);

        // Checks if there's any particles to be removed
        bool particles_to_remove();
        std::vector<int> pop_removed_particles();
    };
}
