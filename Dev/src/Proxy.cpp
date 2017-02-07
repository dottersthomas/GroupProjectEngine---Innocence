#include "Proxy.h"

Proxy * Proxy::s_Instance_ = 0;

void Proxy::requestCursorPositionChange(double pX, double pY) {
	m_WindowManager_->setCursorPosition(pX, pY);
}

void Proxy::requestWindowSize(int &pWidth, int &pHeight) {
	glfwGetWindowSize(m_WindowManager_->getWindow(), &pWidth, &pHeight);
}

void Proxy::requestCursorPos(double &pX, double &pY) {
	glfwGetCursorPos(m_WindowManager_->getWindow(), &pX, &pY);
}

void Proxy::setUIFocus(bool pToggle) {
	m_WindowManager_->setUIfocus(pToggle);
}

void Proxy::requestCursorDrawChange(bool ptoggle) {
	m_WindowManager_->toggleCursorDraw(ptoggle);
}

void Proxy::requestScoreIncrease(int pAmount) {
	m_Game_->setScore(m_Game_->getScore() + pAmount);
}

