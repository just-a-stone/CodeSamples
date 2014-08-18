<?php

class Session {

	private $authenticated = false;
	private $userName = null;

	/**
	 * @return A session object corresponding to the current session.
	 */
	public static function getSession() {
		// start a new session
		session_start();

		// get or create the session object
		$session = $_SESSION['session'];
		if ($session == null) {
			$session = new Session();
			$_SESSION['session'] = $session;
		}

		return $session;
	}


	/**
	 * @return <code>true</code> if this session is authenticated, <code>false</code> otherwise.
	 */
	public function isAuthenticated() {
		return $this->authenticated;
	}


	public function getUserName() {
		return $this->userName;
	}


	public function login($username, $password) {
		if ($username == "andreas" && $password == "helloWorld") {
			session_regenerate_id(true);
			$this->authenticated = true;
			$this->userName = $username;
		}
	}


	/**
	 * Logout from the current session.
	 * After this method has been called, the session is again in "not authenticated" state.
	 */
	public function logout() {
		$authenticated = false;
		$userName = null;

		$_SESSION = array();

		if (ini_get("session.use_cookies")) {
			$params = session_get_cookie_params();
			setcookie(session_name(), '', time() - 42000, $params["path"],
			$params["domain"], $params["secure"], $params["httponly"]
			);
		}
		session_destroy();
	}


	/**
	 * @return A readable string of this session object, including the session object attributes.
	 */
	public function toString() {
		return "Session[authenticated:" . $this->authenticated . ", userName:" . $this->userName . "]";
	}
}



class Page {

	private $header= "";
	private $body = "";

	public function __construct() {
		$this->header ="<!DOCTYPE html>\n" .
				"<html>\n" .
				"\n" .
				"<head>\n" .
				"<meta charset=\"UTF-8\">\n" .
				"<title>Login</title>\n" .
				"</head>\n" .
				"\n" .
				"<body>\n";
	}


	public function addFile($htmlFile) {
		$this->body = $this->body . file_get_contents($htmlFile);
	}


	public function replaceMarkers($markers) {
		foreach($markers as $key => $val) {
			$this->body = str_replace($key, $val, $this->body);
		}
	}


	public function sendResponse() {
		echo $this->header . $this->body . "</body></html>";
	}
}

?>