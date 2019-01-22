// Enhancements:
//
// Close event
// double buffering
// menu
// undo
// quit
// restart
// new game
// select game
// scooby cards
// resizeable
// check for winner
// cheat mode

#include <vector>

const int cellToCardMargin = 2;
const int spaceBetweenCells = 10;
const int verticalDropBetweenCards = 22;
const int maxCardsPerCell = 19; // the original 7 + 12 moved onto it.

class Cell
{
public:
	Cell(int l, int t, int r, int b);
	virtual void Draw(CPaintDC &dc);
	virtual bool CanRemoveCard();
	virtual bool CanAcceptCard(int index);
	void AddCard(int index);
	int RemoveCard();
	bool IsPointWithinCell(CPoint point); 
	int GetCardOnTop(); // or -1 if none there.
	void SetSelected(bool selected);
	bool isRed(int suit);
protected:
	std::vector <int> mCards;
	int mLeft, mTop, mRight, mBottom;
	bool mSelected;
};

class TempCell : public Cell
{
public:
	TempCell(int l, int t, int r, int b);
};

class EndCell : public Cell
{
public:
	EndCell(int l, int t, int r, int b);
	virtual bool CanRemoveCard();
	virtual bool CanAcceptCard(int index);
};

class StartCell : public Cell
{
public:
	StartCell(int l, int t, int r, int b);
	virtual void Draw(CPaintDC &dc);
	virtual bool CanAcceptCard(int index);
};

