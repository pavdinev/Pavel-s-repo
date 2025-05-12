from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import Select

import time

# Set up the Chrome WebDriver
service = Service(executable_path=r"C:\Users\Pavel\Downloads\chromedriver-win64\chromedriver.exe")
driver = webdriver.Chrome(service=service)

def click_text_button(driver, text_selector, timeout):
    """
    Waits for and clicks the button with given CSS selector.
    """
    try:
        button = WebDriverWait(driver, timeout).until(
            EC.element_to_be_clickable((By.CSS_SELECTOR, text_selector))
        )
        button.click()
        time.sleep(1)  # Give some time for the message to appear
    except Exception as e:
        print(f"Failed to click button: {e}")
        print(repr(e))

def click_select_button(driver, text_drop_down, timeout):
    """
    Waits for and clicks the button with given CSS selector.
    """
    try:
        dropdown = WebDriverWait(driver, timeout).until(
            EC.presence_of_element_located((By.NAME, "sort_by"))
        )

        # Create a Select object
        select = Select(dropdown)

        # Select the option by value
        select.select_by_value(text_drop_down)  # or "name", or "" for default
        time.sleep(1)  # Give some time for the message to appear
    except Exception as e:
        print(f"Failed to click button: {e}")
        print(repr(e))


def check_message(driver, message_selector, expected_text="Hello", timeout=5):
    """
    Verifies if a message appears with the expected text.
    """
    try:
        message = WebDriverWait(driver, timeout).until(
            EC.visibility_of_element_located((By.CSS_SELECTOR, message_selector))
        )
        if message.text.strip() == expected_text:
            print("✅ Success: Message 'Hello' appeared!")
        else:
            print(f"❌ Message found, but text was: '{message.text}'")
    except Exception as e:
        print(f"❌ Failed to find message: {e}")


# Run test
driver.get("http://127.0.0.1:8000/")
time.sleep(1)

# Click button
text_button_selector = 'button[data-selector="text_button"]'
click_text_button(driver,text_button_selector,timeout=5)


# Check if message appeared
text_button_message_selector = '[data-selector="button_message"]'
check_message(driver, text_button_message_selector,timeout=5)

# Click url
url_click_selector_message = 'a[data-selector="url_button"]'
click_text_button(driver, url_click_selector_message,timeout = 10)

# Click drop down age
drop_down_click_message = "name"
click_select_button(driver, drop_down_click_message,timeout = 100)

# Click sort name
drop_down_click_message = "age"
click_select_button(driver, drop_down_click_message,timeout = 100)


# Close browser
driver.quit()
