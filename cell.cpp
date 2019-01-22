#include "stdafx.h" // This must be included first
#include <afxwin.h>
#include "cell.h"
#include "WindowsCards.h"

Cell::Cell(int l, int t, int r, int b)
{
	mLeft = l;
	mTop = t;
	mRight = r;
	mBottom = b;

	mSelected = false;
}
void Cell::Draw(CPaintDC &dc)
{
	dc.Rectangle(mLeft , mTop, mRight, mBottom);
	if (mCards.size() > 0)
	{
		DrawCard(dc, mLeft + cellToCardMargin, mTop + cellToCardMargin, mCards.back(), mSelected);
	}

}
bool Cell::CanRemoveCard()
{
	return true;
}
bool Cell::CanAcceptCard(int index) 
{
	if (mCards.size() == 0) {
		return true;
	}
	else {
		return false;
	}
}
void Cell::AddCard(int index)
{
	mCards.push_back(index);
}
int Cell::RemoveCard()
{
	int temp = mCards.back();
	mCards.pop_back();
	return temp;
}
bool Cell::IsPointWithinCell(CPoint point)
{
	if ((point.x > mLeft && point.x < mRight) && (point.y > mTop && point.y < mBottom + 140)) {
		return true;
	}
	else {
		return false;
	}
}
int Cell::GetCardOnTop() // or -1 if none there.
{
	if (mCards.size() == 0) {
		return -1;
	}
	else {
		return mCards.back();
	}
}
void Cell::SetSelected(bool selected)
{
	mSelected = selected;
}


TempCell::TempCell(int l, int t, int r, int b) : Cell(l,t,r,b)
{

}


EndCell::EndCell(int l, int t, int r, int b) : Cell(l, t, r, b)
{
}
bool EndCell::CanRemoveCard()
{
	return false;
}
bool EndCell::CanAcceptCard(int index)
{
	//ace first then same suit and one more.
	int SCrank = index / 4;
	int SCsuit = index % 4;

	if (mCards.size() == 0 && SCrank != 0) {
		return false;
	}
	if (mCards.size() == 0 && SCrank == 0) { //if cell is empty and selected card rank is an ace
		return true;
	}
	int TCrank = mCards.back() / 4;
	int TCsuit = mCards.back() % 4;

	if ((SCsuit == TCsuit) && (TCrank == SCrank - 1)) {
		return true;
	}
	return false;
}


StartCell::StartCell(int l, int t, int r, int b) : Cell(l, t, r, b)
{
}

void StartCell::Draw(CPaintDC & dc)
{
	dc.Rectangle(mLeft , mTop, mRight, mBottom); //only make last card selected
	for (int i = 0; i < mCards.size(); i++) {
		if (i == mCards.size() - 1) {
			DrawCard(dc, mLeft + cellToCardMargin, mTop + cellToCardMargin + (i*verticalDropBetweenCards), mCards[i], mSelected);
		}
		else {
			DrawCard(dc, mLeft + cellToCardMargin, mTop + cellToCardMargin + (i*verticalDropBetweenCards), mCards[i], false);
		}
	}
}

bool StartCell::CanAcceptCard(int index)
{
	//look at top card needs to be one less in rank and opisite color. or empty takes anything
	if (mCards.size() == 0) {
		return true;
	}
	int topcard = mCards.back();
	int TCrank = topcard / 4; 
	int TCsuit = topcard % 4;

	int SCrank = index / 4;
	int SCsuit = index % 4;

	if ((isRed(TCsuit) == true && isRed(SCsuit) == false) && (TCrank == SCrank + 1)) {
		return true;
	}
	if ((isRed(TCsuit) == false && isRed(SCsuit) == true) && (TCrank == SCrank + 1)) {
		return true;
	}
	return false;


}

bool Cell::isRed(int suit) {
	if (suit == 1 || suit == 2) {
		return true;
	}
	else {
		return false;
	}
}
