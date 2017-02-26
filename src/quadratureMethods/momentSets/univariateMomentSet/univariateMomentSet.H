/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2014-2016 Alberto Passalacqua
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is derivative work of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::univariateMomentSet

Description
    Stores a generic moment set with the corresponding list of orders.

SourceFiles
    univariateMomentSet.C
    univariateMomentSet.H

\*---------------------------------------------------------------------------*/

#ifndef univariateMomentSet_H
#define univariateMomentSet_H

#include "momentSet.H"
#include "scalarMatrices.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                    Class univariateMomentSet Declaration
\*---------------------------------------------------------------------------*/

class univariateMomentSet
:
    public momentSet
{
    // Private data

        //- Alpha coefficients of the recurrence relation
        scalarList alpha_;

        //- Beta coefficients of the recurrence relation
        scalarList beta_;

        //- Position of first negative zeta
        label negativeZeta_;

        //- Bool to indicate if moment set is degenerate, with only the
        //  zero-order moment realizable
        bool degenerate_;

        //- Bool to indicate if the full moment set is realizable
        bool fullyRealizable_;

        //- Bool to indicate if a subset of the full moment set is realizable
        bool subsetRealizable_;

        //- Bool to indicate if the moment set is on the boundary of the
        //  moment space
        bool onMomentSpaceBoundary_;

        //- Bool to indicate moment realizability was checked
        bool realizabilityChecked_;

        //- Number of realizable moments
        label nRealizableMoments_;

     // Private member functions

        //- Check moment realizability
        void checkRealizability();

        //- Checks canonical moments for measures with support over [0,1]
        void checkCanonicalMoments
        (
            const scalarList& zeta,
            const label nZeta
        );


public:

    // Constructors

        //- Construct from number of moments and initial value
        univariateMomentSet
        (
            const label nMoments,
            const labelListList& momentOrders,
            const word& support,
            const label nFixedQuadraturePoints = 0
        );

        //- Construct from scalarList
        univariateMomentSet
        (
            const scalarList& m,
            const labelListList& momentOrders,
            const word& support,
            const label nFixedQuadraturePoints = 0
        );

    //- Destructor
    virtual ~univariateMomentSet();


    // Member Functions

        //- Returns alpha coefficients of the recurrence relation
        const scalarList& alphaRecurrence() const;

        //- Returns alpha coefficients of the recurrence relation
        scalarList& alphaRecurrence();

        //- Returns beta coefficients of the recurrence relation
        const scalarList& betaRecurrence() const;

        //- Returns beta coefficients of the recurrence relation
        scalarList& betaRecurrence();

        //- Returns degenerate status of the moment set
        inline bool isDegenerate();

        //- Return realizability status of the moment set
        inline bool isFullyRealizable();

        //- Return realizability status of the moment subsets
        inline bool isSubsetRealizable();

        //- Return true if the moment set is on the boundary of the moment space
        inline bool isOnMomentSpaceBoundary();

        //- Return the number of realizable moments
        inline label nRealizableMoments();

        //- Update moments from the corresponding quadrature
        void update
        (
            const scalarList& weights,
            const scalarList& abscissae
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "univariateMomentSetI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //