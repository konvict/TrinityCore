/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TRINITY_IDLEMOVEMENTGENERATOR_H
#define TRINITY_IDLEMOVEMENTGENERATOR_H

#include "MovementGenerator.h"
#include "Optional.h"
#include "Timer.h"

enum RotateDirection : uint8;

class IdleMovementGenerator : public MovementGenerator
{
    public:
        explicit IdleMovementGenerator();

        void Initialize(Unit*) override;
        void Reset(Unit*) override;
        bool Update(Unit*, uint32) override { return true; }
        void Deactivate(Unit*) override;
        void Finalize(Unit*, bool, bool) override;
        MovementGeneratorType GetMovementGeneratorType() const override;
};

class RotateMovementGenerator : public MovementGenerator
{
    public:
        static constexpr float MIN_ANGLE_DELTA_FOR_FACING_UPDATE = 0.05f;

        explicit RotateMovementGenerator(uint32 id, RotateDirection direction, Optional<Milliseconds> duration,
            Optional<float> turnSpeed, Optional<float> totalTurnAngle);

        void Initialize(Unit*) override;
        void Reset(Unit*) override;
        bool Update(Unit*, uint32) override;
        void Deactivate(Unit*) override;
        void Finalize(Unit*, bool, bool) override;
        MovementGeneratorType GetMovementGeneratorType() const override;

    private:
        uint32 _id;
        Optional<TimeTracker> _duration;
        Optional<float> _turnSpeed;         ///< radians per sec
        Optional<float> _totalTurnAngle;
        RotateDirection _direction;
        uint32 _diffSinceLastUpdate;
};

class DistractMovementGenerator : public MovementGenerator
{
    public:
        explicit DistractMovementGenerator(uint32 timer, float orientation);

        void Initialize(Unit*) override;
        void Reset(Unit*) override;
        bool Update(Unit*, uint32) override;
        void Deactivate(Unit*) override;
        void Finalize(Unit*, bool, bool) override;
        MovementGeneratorType GetMovementGeneratorType() const override;

    private:
        uint32 _timer;
        float _orientation;
};

class AssistanceDistractMovementGenerator : public DistractMovementGenerator
{
    public:
        explicit AssistanceDistractMovementGenerator(uint32 timer, float orientation);

        void Finalize(Unit*, bool, bool) override;
        MovementGeneratorType GetMovementGeneratorType() const override;
};

#endif
