/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2018 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    GNECrossingFrame.h
/// @author  Pablo Alvarez Lopez
/// @date    Oct 2016
/// @version $Id$
///
// The Widget for add Crossing elements
/****************************************************************************/
#ifndef GNECrossingFrame_h
#define GNECrossingFrame_h


// ===========================================================================
// included modules
// ===========================================================================
#include "GNEFrame.h"

// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class GNECrossingFrame
 * The Widget for setting internal attributes of Crossing elements
 */
class GNECrossingFrame : public GNEFrame {

public:

    // ===========================================================================
    // class CurrentJunction
    // ===========================================================================

    class CurrentJunction : public FXGroupBox {

    public:
        /// @brief constructor
        CurrentJunction(GNECrossingFrame* crossingFrameParent);

        /// @brief destructor
        ~CurrentJunction();

        /// @brief set current junction label
        void updateCurrentJunctionLabel(const std::string &junctionID);

    private:
        /// @brief Label for current Junction
        FXLabel* myCurrentJunctionLabel;

    };

    // ===========================================================================
    // class EdgesSelector
    // ===========================================================================

    class EdgesSelector : public FXGroupBox {
        /// @brief FOX-declaration
        FXDECLARE(GNECrossingFrame::EdgesSelector)

    public:
        /// @brief constructor
        EdgesSelector(GNECrossingFrame* crossingFrameParent);

        /// @brief destructor
        ~EdgesSelector();

        /// @brief get current junction
        GNEJunction* getCurrentJunction() const;

        /// @brief enable edgeSelector
        void enableEdgeSelector(GNEJunction* currentJunction);

        /// @brief disable edgeSelector
        void disableEdgeSelector();

        /// @brief restore colors of all edges
        void restoreEdgeColors();

        /// @brief return candidate color
        const RGBColor& getCandidateColor() const;

        /// @brief return selected color
        const RGBColor& getSelectedColor() const;

        /// @name FOX-callbacks
        /// @{
        /// @brief called when useSelectedEdges button edge is pressed
        long onCmdUseSelectedEdges(FXObject*, FXSelector, void*);

        /// @brief called when clear selection button is pressed
        long onCmdClearSelection(FXObject*, FXSelector, void*);

        /// @brief called when invert selection button is pressed
        long onCmdInvertSelection(FXObject*, FXSelector, void*);
        /// @}

    protected:
        /// @brief FOX needs this
        EdgesSelector() {}

    private:
        /// @brief pointer to GNECrossingFrame parent
        GNECrossingFrame* myCrossingFrameParent;

        /// @brief CheckBox for selected edges
        FXButton* myUseSelectedEdges;

        /// @brief button for clear selection
        FXButton* myClearEdgesSelection;

        /// @brief button for invert selection
        FXButton* myInvertEdgesSelection;

        /// @brief current Junction
        GNEJunction* myCurrentJunction;
    };

    // ===========================================================================
    // class CrossingParameters
    // ===========================================================================

    class CrossingParameters : public FXGroupBox {
        /// @brief FOX-declaration
        FXDECLARE(GNECrossingFrame::CrossingParameters)

    public:
        /// @brief constructor
        CrossingParameters(GNECrossingFrame* crossingFrameParent);

        /// @brief destructor
        ~CrossingParameters();

        /// @brief enable crossing parameters and set the default value of parameters
        void enableCrossingParameters(bool hasTLS);

        /// @brief disable crossing parameters and clear parameters
        void disableCrossingParameters();

        /// @brief check if currently the CrossingParameters is enabled
        bool isCrossingParametersEnabled() const;

        /// @brief mark or dismark edge
        void markEdge(GNEEdge* edge);

        /// @brief clear edges
        void clearEdges();

        /// @brief invert edges
        void invertEdges(GNEJunction* parentJunction);

        /// @brief use selected eges
        void useSelectedEdges(GNEJunction* parentJunction);

        /// @brief get crossing NBedges
        std::vector<NBEdge*> getCrossingEdges() const;

        /// @brief get crossing priority
        bool getCrossingPriority() const;

        /// @brief get crossing width
        double getCrossingWidth() const;

        /// @brief get candidate color
        const RGBColor& getCandidateColor() const;

        /// @brief get selected color
        const RGBColor& getSelectedColor() const;

        /// @brief check if current parameters are valid
        bool isCurrentParametersValid() const;

        /// @name FOX-callbacks
        /// @{
        /// @brief Called when user set a value
        long onCmdSetAttribute(FXObject*, FXSelector, void*);

        /// @brief Called when help button is pressed
        long onCmdHelp(FXObject*, FXSelector, void*);
        /// @}

    protected:
        /// @brief FOX needs this
        CrossingParameters() {}

    private:
        /// @brief pointer to GNECrossingFrame parent
        GNECrossingFrame* myCrossingFrameParent;

        /// @brief current selected edges
        std::vector<GNEEdge*> myCurrentSelectedEdges;

        /// @brief Label for edges
        FXLabel* myCrossingEdgesLabel;

        /// @brief TextField for edges
        FXTextField* myCrossingEdges;

        /// @brief Label for Priority
        FXLabel* myCrossingPriorityLabel;

        /// @brief CheckBox for Priority
        FXCheckButton* myCrossingPriorityCheckButton;

        /// @brief Label for width
        FXLabel* myCrossingWidthLabel;

        /// @brief TextField for width
        FXTextField* myCrossingWidth;

        /// @brief button for help
        FXButton* myHelpCrossingAttribute;

        /// @brief flag to check if current parameters are valid
        bool myCurrentParametersValid;

        /// @brief color for candidate edges
        RGBColor myCandidateColor;

        /// @brief color for selected edges
        RGBColor mySelectedColor;
    };

    // ===========================================================================
    // class CreateCrossing
    // ===========================================================================

    class CreateCrossing : public FXGroupBox {
        /// @brief FOX-declaration
        FXDECLARE(GNECrossingFrame::CreateCrossing)

    public:
        /// @brief constructor
        CreateCrossing(GNECrossingFrame* crossingFrameParent);

        /// @brief destructor
        ~CreateCrossing();

        /// @brief enable or disable button create crossing
        void setCreateCrossingButton(bool value);

        /// @name FOX-callbacks
        /// @{
        /// @brief Called when the user press the button create edge
        long onCmdCreateCrossing(FXObject*, FXSelector, void*);
        /// @}

    protected:
        /// @brief FOX needs this
        CreateCrossing() {}

    private:
        /// @brief pointer to crossingFrame parent
        GNECrossingFrame* myCrossingFrameParent;

        /// @field FXButton for create Crossing
        FXButton* myCreateCrossingButton;
    };

    /**@brief Constructor
     * @brief parent FXHorizontalFrame in which this GNEFrame is placed
     * @brief viewNet viewNet that uses this GNEFrame
     */
    GNECrossingFrame(FXHorizontalFrame* horizontalFrameParent, GNEViewNet* viewNet);

    /// @brief Destructor
    ~GNECrossingFrame();

    /// @brief hide crossing frame
    void hide();

    /**@brief add Crossing element
     * @param objectsUnderCursor collection of objects under cursor after click over view
     * @return true if a GNECrossing was added, false in other case
     */
    bool addCrossing(const GNEViewNet::ObjectsUnderCursor &objectsUnderCursor);

    /// @brief create crossing (used when user press ENTER key in Crossing mode)
    void createCrossingHotkey();

protected:
    /// @brief FOX needs this
    GNECrossingFrame() {}

private:
    /// @brief current junction modul
    GNECrossingFrame::CurrentJunction* myCurrentJunction;

    /// @brief edge selector modul
    GNECrossingFrame::EdgesSelector* myEdgeSelector;

    /// @brief crossing parameters modul
    GNECrossingFrame::CrossingParameters* myCrossingParameters;

    /// @brief create crossing modul
    GNECrossingFrame::CreateCrossing* myCreateCrossing;
};


#endif

/****************************************************************************/
