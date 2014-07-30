package main

import "bytes"
import "encoding/json"
import "fmt"
import "log"
import "io/ioutil"
import "net/http"

type Hue struct {
	IpAddress  string
	UserName   string
	DeviceType string
}

func processJsonResponse(resp *http.Response, jsonBody interface{}) error {
	defer resp.Body.Close()

	if resp.StatusCode != 200 {
		err := fmt.Errorf("Http request failed: Status %d", resp.StatusCode)
		log.Printf("%v", err)
		return err
	}

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Printf("Failed to read response body: %v", err)
		return err
	}

	err = json.Unmarshal(body, &jsonBody)
	if err != nil {
		log.Printf("Failed to parse response body: %v", err)
		return err
	}

	return nil
}

func (hue *Hue) get(path string, jsonBody interface{}) error {
	url := "http://" + hue.IpAddress + path

	resp, err := http.Get(url)
	if err != nil {
		log.Printf("Http GET failed: %v", err)
		return err
	}

	if err = processJsonResponse(resp, jsonBody); err != nil {
		return err
	}

	return nil
}

func (hue *Hue) post(path string, reqBody interface{}, respBody interface{}) error {
	url := "http://" + hue.IpAddress + path

	data, err := json.Marshal(reqBody)
	if err != nil {
		log.Printf("Unable to create JSON for request: %v", err)
		return err
	}
	reqReader := bytes.NewReader(data)

	resp, err := http.Post(url, "application/json", reqReader)
	if err != nil {
		log.Printf("Http POST failed: %v", err)
		return err
	}

	if err = processJsonResponse(resp, respBody); err != nil {
		return err
	}

	return nil
}

func (hue *Hue) put(path string, reqBody interface{}, respBody interface{}) error {
	url := "http://" + hue.IpAddress + path

	data, err := json.Marshal(reqBody)
	if err != nil {
		log.Printf("Unable to create JSON for request: %v", err)
		return err
	}
	log.Printf("Request body: %v", string(data))
	reqReader := bytes.NewReader(data)

	req, err := http.NewRequest("PUT", url, reqReader)
	if err != nil {
		log.Printf("Creating PUT request failed: %v", err)
	}

	req.Header.Add("Content-Type", "application/json")

	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		log.Printf("Http PUT failed: %v", err)
		return err
	}

	if err = processJsonResponse(resp, respBody); err != nil {
		return err
	}

	return nil
}

// User Info

type UserInfoResponseBody struct {
	Lights map[string]struct {
		State struct {
			On        bool
			Hue       int32
			Sat       int32
			Bri       int32
			Alert     string
			ColorMode string
			ct        int32
			Effect    string
			Reachable bool
			XY        []float64
		}
		TypeString  string `type`
		Name        string
		ModelId     string
		SWVersion   string
		PointSymbol map[string]string
	}
	Groups map[string]interface{}
	Config struct {
		Gateway   string
		LocalTime string
		ProxyPort int32
		Whitelist map[string]struct {
			LastUseDate string `last use date`
			CreateDate  string `create date`
			Name        string
		}
		SWUpdate struct {
			Notify      bool
			UpdateState int32
			Url         string
			Text        string
		}
		LinkButton       bool
		PortalServices   bool
		PortalConnection string
		ProxyAddress     string
		UTC              string
		SWVersion        string
		ApiVersion       string
		Netmask          string
		Timezone         string
		PortalState      struct {
			Incoming   bool
			Outgoing   bool
			SignedOn   bool
			Connection string
		}
		Name string
		Mac  string
	}
	Schedules map[string]interface{}
	Scenes    map[string]struct {
		Name   string
		Active bool
		Lights []string
	}
}

func (hue *Hue) FetchUserInfo() error {
	log.Printf("Fetching user info...")

	path := "/api/" + hue.UserName

	// var jsonBody map[string]interface{}
	var jsonBody UserInfoResponseBody
	if err := hue.get(path, &jsonBody); err != nil {
		log.Printf("Failed to fetch user info: %v", err)
		return err
	}

	log.Printf("Got user info: %v", jsonBody)

	return nil
}

// User Registration

type UserRegistrationRequestBody struct {
	Username   string `json:"username"`
	DeviceType string `json:"devicetype"`
}

func (hue *Hue) RegisterUser() error {
	log.Printf("Registering user...")

	path := "/api"

	reqBody := &UserRegistrationRequestBody{
		hue.UserName,
		hue.DeviceType,
	}

	var respBody map[string]interface{}
	if err := hue.post(path, &reqBody, respBody); err != nil {
		log.Printf("Failed to register user: %v", err)
		return err
	}

	log.Printf("Registered user: %v", respBody)

	return nil
}

// Fetching Light State

type LightsResponseBody map[string]struct {
	name string
}

func (hue *Hue) FetchLights(resp *LightsResponseBody) error {
	log.Printf("Fetching current lights...")

	path := "/api/" + hue.UserName + "/lights"

	if err := hue.get(path, resp); err != nil {
		log.Printf("Failed to fetch lights: %v", err)
		return err
	}

	log.Printf("Got light info: %v", resp)

	return nil
}

// Setting Light State

type LightRequestBody struct {
	On  bool  `json:"on"`
	Hue int32 `json:"hue"`
	Sat int32 `json:"sat"`
	Bri int32 `json:"bri"`
}

func (hue *Hue) ChangeLight(id string, state *LightRequestBody) error {
	log.Printf("Changing light state...")

	path := "/api/" + hue.UserName + "/lights/" + id + "/state"
	log.Printf("path: %v", path)

	var jsonBody []interface{}
	if err := hue.put(path, state, &jsonBody); err != nil {
		log.Printf("Failed to change light state: %v", err)
		return err
	}

	log.Printf("Response json: %v", jsonBody)

	return nil
}

// Main

func main() {
	hue := &Hue{
		"192.168.1.3",
		"CandelabraUserName",
		"CandelabraDeviceType",
	}

	// hue.FetchUserInfo()
	// hue.FetchLights()

	state := &LightRequestBody{
		true, 127, 127, 127,
	}
	hue.ChangeLight("3", state)
}
