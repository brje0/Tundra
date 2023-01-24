#pragma once

#include <vector>
#include <variant>
#include <stdexcept>
#include <functional>

#include "../lib/subhook/subhook.h"
#include "engine_structs.hpp"

#ifndef HOOK_FLAGS
#define HOOK_FLAGS subhook::HookFlags::HookFlag64BitOffset
#endif

const char DEFAULT_HOOK_PRIORITY = 0;
extern const char NOT_SPECIAL;

template <typename ParentHookSignature, typename ChildHookSignature, typename ChildPostHookSignature>
class FunctionHook;

// Shorthand for function types.
typedef FunctionHook<void(), bool(), void()> voidFuncHook;
typedef FunctionHook<void(int ID), bool(int &ID), void(int ID)> voidIntFuncHook;
typedef FunctionHook<void(int ID1, int ID2), bool(int &ID1, int &ID2), void(int ID1, int ID2)> voidDoubleIntFuncHook;
typedef FunctionHook<void(int ID1, int ID2, int ID3), bool(int &ID1, int &ID2, int &ID3),
                          void(int ID1, int ID2, int ID3)> voidTripleIntFuncHook;
typedef FunctionHook<int(int identifier, unsigned int ticket), bool(int &identifier, unsigned int &ticket),
                     void(int ID, int identifier, unsigned int ticket)> createAccountByJoinTicketFuncHook;
typedef FunctionHook<void(unsigned int address, unsigned int port, int unk, const char* message), 
                     bool(unsigned int &address, unsigned int &port, int &unk, char* &message),
                     void(unsigned int address, unsigned int port, int unk, const char* message)> serverSendConnectResponseFuncHook;
typedef FunctionHook<int(int itemID, int childItemID, int parentHumanID, int slot),
                     bool(int &itemID, int &childItemID, int &parentHumanID, int &slot),
                     void(bool worked, int itemID, int childItemID, int parentHumanID, int slot)> linkItemFuncHook;
typedef FunctionHook<int(int itemID, unsigned int character), bool(int &itemID, unsigned int character),
                     void(int itemID, unsigned int character)> itemComputerInputFuncHook;
typedef FunctionHook<void(int humanID, int bone, int unk, int damage), bool(int &humanID, int &bone, int &unk, int &damage),
                     void(int humanID, int bone, int unk, int damage)> humanApplyDamageFuncHook;
typedef FunctionHook<void(int humanID, int trunkBoneID, int branchBoneID,
                     Vector* destination, RotMatrix* destinationAxis,
                     Vector* vecA, float a, float rot,
                     float strength, float* d,
                     Vector* vecB, Vector* vecC, Vector* vecD,
                     char flags), bool(int &humanID, int &trunkBoneID, int &branchBoneID,
                     Vector* &destination, RotMatrix* &destinationAxis,
                     Vector* &vecA, float &a, float &rot,
                     float &strength, float* &d,
                     Vector* &vecB, Vector* &vecC, Vector* &vecD,
                     char &flags), void(int humanID, int trunkBoneID, int branchBoneID,
                     Vector* destination, RotMatrix* destinationAxis,
                     Vector* vecA, float a, float rot,
                     float strength, float* d,
                     Vector* vecB, Vector* vecC, Vector* vecD,
                     char flags)> humanLimbInverseKinematicsFuncHook;
typedef FunctionHook<void(int aBodyID, int bBodyID, Vector* aLocalPos,
                  Vector* bLocalPos, Vector* normal, float a,
                  float b, float c, float d), bool(int &aBodyID, 
                  int &bBodyID, Vector* &aLocalPos, Vector* &bLocalPos,
                  Vector* &normal, float &a, float &b, float &c, float &d),
                  void(int aBodyID, int bBodyID, Vector* aLocalPos,
                  Vector* bLocalPos, Vector* normal, float a,
                  float b, float c, float d)> collideBodiesFuncHook;
typedef FunctionHook<void(int bodyID, Vector* localPos, Vector* normal,
                  float a, float b, float c, float d), 
                  bool(int &bodyID, Vector* &localPos, Vector* &normal,
                  float &a, float &b, float &c, float &d),
                  void(int bodyID, Vector* localPos, Vector* normal,
                  float a, float b, float c, float d)> collideBodyWithLevelFuncHook;
typedef FunctionHook<int(), bool(), void(int ID)> createPlayerFuncHook;
typedef FunctionHook<int(Vector* pos, RotMatrix* rot, int playerID), bool(Vector* &pos, RotMatrix* &rot, int &playerID),
                     void(int humanID, Vector* pos, RotMatrix* rot, int playerID)> createHumanFuncHook;
typedef FunctionHook<int(int type, Vector* pos, Vector* vel, RotMatrix* rot), bool(int &type, Vector* &pos, Vector* &vel,
                     RotMatrix* &rot), void(int itemID, int type, Vector* pos, Vector* vel, RotMatrix* rot)> createItemFuncHook;
typedef FunctionHook<int(int type, Vector* pos, Vector* vel, RotMatrix* rot, int color), bool(int &type, Vector* &pos, 
                     Vector* &vel, RotMatrix* &rot, int &color), void(int vehicleID, int type, Vector* pos, Vector* vel,
                     RotMatrix* rot, int color)> createVehicleFuncHook;
typedef FunctionHook<int(int type, Vector* pos, RotMatrix* rot, Vector* vel,
                 Vector* scale, float mass), bool(int &type, Vector* &pos,
                 RotMatrix* &rot, Vector* &vel, Vector* &scale, float &mass),
                 void(int rigidBodyID, int type, Vector* pos, RotMatrix* rot, Vector* vel,
                 Vector* scale, float mass)> createRigidBodyFuncHook;
typedef FunctionHook<int(int playerID, char* message), bool(int &playerID, char* &message), void(int playerID, char* message)> serverPlayerMessageFuncHook;
typedef FunctionHook<void(int type, char* message, int speakerID, int distance), bool(int &type, char* &message, int &speakerID,
                          int &distance), void(int type, char* message, int speakerID, int distance)> eventMessageFuncHook;
typedef FunctionHook<void(int vehicleID, int updateType, int partID,
                     Vector* pos, Vector* normal),
                     bool(int &vehicleID, int &updateType, int &partID,
                     Vector* &pos, Vector* &normal),
                     void(int vehicleID, int updateType, int partID,
                     Vector* pos, Vector* normal)> eventUpdateVehicleFuncHook;
typedef FunctionHook<void(int soundType, Vector* pos, float volume, float pitch), bool(int &soundType, Vector* &pos, float &volume,
                     float &pitch), void(int soundType, Vector* pos, float volume, float pitch)> eventSoundFuncHook;
typedef FunctionHook<void(int unk, int hitType, Vector* pos, Vector* normal), bool(int &unk, int &hitType, Vector* &pos, 
                     Vector* &normal), void(int unk, int hitType, Vector* pos, Vector* normal)> eventBulletHitFuncHook;
typedef FunctionHook<void(int param_1, int param_2, int param_3, int param_4,
                     int param_5, int param_6, int* param_7, int* param_8),
                     bool(int &param_1, int &param_2, int &param_3, int &param_4,
                     int &param_5, int &param_6, int* param_7, int* param_8),
                     void(int param_1, int param_2, int param_3, int param_4,
                     int param_5, int param_6, int* param_7, int* param_8)> eventGlassBreakFuncHook;

// Wrapper for hooks.
template <typename ParentHookSignature, typename ChildHookSignature, typename ChildPostHookSignature>
class FunctionHook
{
public:
    void install(ParentHookSignature* targetFunction_in, ParentHookSignature* hookFunction_in)
    {
        targetFunction = targetFunction_in;
        hookFunction = hookFunction_in;
        if (!hook.Install((void *)targetFunction, (void *)hookFunction, HOOK_FLAGS))
            throw std::runtime_error("Failed to install hook.\n");
    }
    unsigned short addHook(std::function<ChildHookSignature> callback)
    {
        return insertByPriority(callback, DEFAULT_HOOK_PRIORITY);
    }
    unsigned short addHook(std::function<ChildHookSignature> callback, char priority)
    {
        return insertByPriority(callback, priority);
    }
    unsigned short hookOnce(std::function<ChildHookSignature> callback)
    {
        unsigned short index = insertByPriority(callback, DEFAULT_HOOK_PRIORITY);
        onceHookParallel[index] = true;
        return index;
    }
    unsigned short hookOnce(std::function<ChildHookSignature> callback, char priority)
    {
        unsigned short index = insertByPriority(callback, priority);
        onceHookParallel[index] = true;
        return index;
    }
    unsigned short addPostHook(std::function<ChildPostHookSignature> postCallback)
    {
        return insertByPriorityPost(postCallback, DEFAULT_HOOK_PRIORITY);
    }
    unsigned short addPostHook(std::function<ChildPostHookSignature> postCallback, char priority)
    {
        return insertByPriorityPost(postCallback, priority);
    }
    unsigned short postHookOnce(std::function<ChildPostHookSignature> postCallback)
    {
        unsigned short index = insertByPriorityPost(postCallback, DEFAULT_HOOK_PRIORITY);
        oncePostHookParallel[index] = true;
        return index;
    }
    unsigned short postHookOnce(std::function<ChildPostHookSignature> postCallback, char priority)
    {
        unsigned short index = insertByPriorityPost(postCallback, priority);
        oncePostHookParallel[index] = true;
        return index;
    }
    void clearOnceHooks()
    {
        for (int i = callbacks.size() - 1; i > -1; i--)
            if (onceHookParallel[i])
                removeHook(i);
    }
    void clearOncePostHooks()
    {
        for (int i = postCallbacks.size() - 1; i > -1; i--)
            if (oncePostHookParallel[i])
                removePostHook(i);
    }
    void removeHook(unsigned short index)
    {
        callbacks.erase(callbacks.begin() + index);
        priorities.erase(priorities.begin() + index);
        parallelInfoVec.erase(parallelInfoVec.begin() + index);
        onceHookParallel.erase(onceHookParallel.begin() + index);
    }
    void removePostHook(unsigned short index)
    {
        postCallbacks.erase(postCallbacks.begin() + index);
        postPriorities.erase(postPriorities.begin() + index);
        parallelInfoVecPost.erase(parallelInfoVecPost.begin() + index);
        oncePostHookParallel.erase(oncePostHookParallel.begin() + index);
    }
    subhook::Hook hook;
    std::vector<std::function<ChildHookSignature>> callbacks;
    std::vector<std::function<ChildPostHookSignature>> postCallbacks;
    std::vector<int> parallelInfoVec;
    std::vector<int> parallelInfoVecPost;
private:
    unsigned short insertByPriority(std::function<ChildHookSignature> callback, char priority)
    {
        if (priorities.size() == 0)
        {
            onceHookParallel.insert(onceHookParallel.begin(), false);
            priorities.insert(priorities.begin(), priority);
            callbacks.insert(callbacks.begin(), callback);
            parallelInfoVec.insert(parallelInfoVec.begin(), NOT_SPECIAL);
            return 0;
        }
        unsigned short i = 0;
        for (char prioNumber : priorities)
        {
            if (priority < prioNumber)
            {
                onceHookParallel.insert(onceHookParallel.begin() + i, false);
                priorities.insert(priorities.begin() + i, priority);
                callbacks.insert(callbacks.begin() + i, callback);
                parallelInfoVec.insert(parallelInfoVec.begin() + i, NOT_SPECIAL);
                return i;
            }
            i++;
        }
        onceHookParallel.push_back(false);
        priorities.push_back(priority);
        callbacks.push_back(callback);
        parallelInfoVec.push_back(NOT_SPECIAL);
        return i;
    }
    unsigned short insertByPriorityPost(std::function<ChildPostHookSignature> postCallback, char priority)
    {
        if (postPriorities.size() == 0)
        {
            oncePostHookParallel.insert(oncePostHookParallel.begin(), false);
            postPriorities.insert(postPriorities.begin(), priority);
            postCallbacks.insert(postCallbacks.begin(), postCallback);
            parallelInfoVecPost.insert(parallelInfoVecPost.begin(), NOT_SPECIAL);
            return 0;
        }
        unsigned short i = 0;
        for (char prioNumber : postPriorities)
        {
            if (priority < prioNumber)
            {
                oncePostHookParallel.insert(oncePostHookParallel.begin() + i, false);
                postPriorities.insert(postPriorities.begin() + i, priority);
                postCallbacks.insert(postCallbacks.begin() + i, postCallback);
                parallelInfoVecPost.insert(parallelInfoVecPost.begin() + i, NOT_SPECIAL);
                return i;
            }
            i++;
        }
        oncePostHookParallel.push_back(false);
        postPriorities.push_back(priority);
        postCallbacks.push_back(postCallback);
        parallelInfoVecPost.push_back(NOT_SPECIAL);
        return i;
    }
    // The priorities of each hook are stored in two different vectors
    // where the index of the hook is the same as the index of the
    // corresponding priority.
    std::vector<char> priorities;
    std::vector<char> postPriorities;
    std::vector<bool> onceHookParallel;
    std::vector<bool> oncePostHookParallel;
    ParentHookSignature* hookFunction;
    ParentHookSignature* targetFunction;
};

template <typename p_ParentFuncHook, typename ChildHookFunc>
class Hook
{
public:
    Hook(p_ParentFuncHook parentHook, ChildHookFunc childHook_in)
    {
        index = parentHook->addHook(childHook_in);
    }
    Hook(p_ParentFuncHook parentHook, ChildHookFunc childHook_in, char priority)
    {
        index = parentHook->addHook(childHook_in, priority);
    }
    unsigned short index;
};

// Similar to above, but only runs once and then is deleted.
template <typename p_ParentFuncHook, typename ChildHookFunc>
class HookOnce
{
public:
    HookOnce(p_ParentFuncHook parentHook, ChildHookFunc childHook_in)
    {
        index = parentHook->hookOnce(childHook_in);
    }
    HookOnce(p_ParentFuncHook parentHook, ChildHookFunc childHook_in, char priority)
    {
        index = parentHook->hookOnce(childHook_in, priority);
    }
    unsigned short index;
};

// Similar to ChildHook, but with a post hook.
template <typename p_ParentFuncHook, typename ChildPostHookFunc>
class PostHook
{
public:
    PostHook(p_ParentFuncHook parentHook, ChildPostHookFunc childPostHook_in)
    {
        index = parentHook->addPostHook(childPostHook_in);
    }
    PostHook(p_ParentFuncHook parentHook, ChildPostHookFunc childPostHook_in, char priority)
    {
        index = parentHook->addPostHook(childPostHook_in, priority);
    }
    unsigned short index;
};

// Similar to ChildHookOnce, but with a post hook.
template <typename p_ParentFuncHook, typename ChildPostHookFunc>
class PostHookOnce
{
public:
    PostHookOnce(p_ParentFuncHook parentHook, ChildPostHookFunc childPostHook_in)
    {
        index = parentHook->postHookOnce(childPostHook_in);
    }
    PostHookOnce(p_ParentFuncHook parentHook, ChildPostHookFunc childPostHook_in, char priority)
    {
        index = parentHook->postHookOnce(childPostHook_in, priority);
    }
    unsigned short index;
};

// A Message From Our President

// Squidward Community College is one of the top universities in the nation working at the intersection of technology,
// the arts and design. We are a university that is shaping the future and improving the world through
// creativity and innovation … We put a high value on bringing goodness to the world.